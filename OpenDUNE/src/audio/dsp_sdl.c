/** @file src/audio/dsp_sdl.c SDL implementation of the DSP. */

#include <assert.h>
#include <SDL.h>
#include "types.h"
#include "../os/endian.h"
#include "../inifile.h"
#include "dsp.h"

#define MIX_OUTPUT_FORMAT AUDIO_S16MSB
#define MIX_OUTPUT_CHANNELS	2
#define MIX_BUFFER_SIZE 1024
#define DEFAULT_OUTPUT_FREQUENCY_INTRO 14000
#define DEFAULT_OUTPUT_FREQUENCY_GAME 11025

static uint8 *s_buffer;
static uint32 s_bufferLen;
static uint8 s_status;
static uint8 *s_data;
static uint32 s_dataLen;
static SDL_AudioSpec s_spec;

static void DSP_Callback(void *userdata, Uint8 *stream, int len)
{
	VARIABLE_NOT_USED(userdata);

	if (s_status == 0 || s_bufferLen == 0 || s_buffer == NULL) {
		/* no more sample to play : */
		SDL_PauseAudio(1);	/* stop playback */
		return;
	}

	if (len <= (int)s_bufferLen) {
		memcpy(stream, s_buffer, len);
		s_bufferLen -= len;
		s_buffer += len;
	} else {	
		s_bufferLen = 0;
		s_buffer = NULL;
		s_status = 0;
		SDL_PauseAudio(1);	/* stop playback */
	}
}

void DSP_Stop(void)
{
	SDL_PauseAudio(1);

	s_bufferLen = 0;
	s_buffer = NULL;
	s_status = 0;
}

void DSP_Uninit(void)
{
	if (SDL_WasInit(SDL_INIT_AUDIO) == 0) return;

	DSP_Stop();
	SDL_CloseAudio();

	free(s_data); s_data = NULL;
	s_dataLen = 0;

	SDL_QuitSubSystem(SDL_INIT_AUDIO);
}

bool DSP_Init(void)
{
	int outputFrequency = DEFAULT_OUTPUT_FREQUENCY_INTRO;
    
    if (SDL_InitSubSystem(SDL_INIT_AUDIO) != 0) return false;
    
	// NOVA_CODER
	outputFrequency = IniFile_GetInteger("output_frequency_intro", DEFAULT_OUTPUT_FREQUENCY_INTRO);
	if (outputFrequency <= 0) { 
		outputFrequency = DEFAULT_OUTPUT_FREQUENCY_INTRO;
	}

	s_spec.freq = outputFrequency;
	s_spec.format = MIX_OUTPUT_FORMAT;
	s_spec.channels = MIX_OUTPUT_CHANNELS;
    s_spec.samples  = MIX_BUFFER_SIZE;
    
	s_spec.callback = DSP_Callback;

	s_bufferLen = 0;
	s_buffer = NULL;
	s_status = 0;
	s_data = NULL;
	s_dataLen = 0;

	if (SDL_OpenAudio(&s_spec, &s_spec) != 0) return false;

	return (SDL_GetAudioStatus() != 0);
}

void DSP_Restart(void) {
  	int outputFrequency = DEFAULT_OUTPUT_FREQUENCY_GAME;
          
    if (SDL_WasInit(SDL_INIT_AUDIO) == 0) return;
      
    DSP_Stop();
	SDL_CloseAudio();
	
	outputFrequency = IniFile_GetInteger("output_frequency_game", DEFAULT_OUTPUT_FREQUENCY_GAME);
	if (outputFrequency <= 0) {
		outputFrequency = DEFAULT_OUTPUT_FREQUENCY_GAME;
	}

	s_spec.freq = outputFrequency;
	s_spec.format = MIX_OUTPUT_FORMAT;
	s_spec.channels = MIX_OUTPUT_CHANNELS;
    s_spec.samples  = MIX_BUFFER_SIZE;

	s_spec.callback = DSP_Callback;

	s_bufferLen = 0;
	s_buffer = NULL;
	s_status = 0;
	s_data = NULL;
	s_dataLen = 0;

	SDL_OpenAudio(&s_spec, &s_spec);
}

static void DSP_ConvertAudio(uint32 freq)
{
    SDL_AudioCVT cvt;

	SDL_BuildAudioCVT(&cvt, AUDIO_U8, 1, freq, s_spec.format, s_spec.channels, s_spec.freq);

    cvt.len = s_bufferLen;
    cvt.buf = (Uint8 *) malloc(cvt.len * cvt.len_mult);
    
    // copy the old data into the buffer
	memcpy(cvt.buf, s_data, s_bufferLen);

	SDL_ConvertAudio(&cvt);

	s_data = cvt.buf;
	s_bufferLen = cvt.len * cvt.len_mult;
}

void DSP_Play(uint8 *data)
{
	DSP_Stop();

	data += READ_LE_UINT16(data + 20);

	if (*data != 1) return;

	s_bufferLen = (READ_LE_UINT32(data) >> 8) - 2;
	
	s_data = realloc(s_data, s_bufferLen);
	memcpy(s_data, data + 6, s_bufferLen);
	
	DSP_ConvertAudio(1000000 / (256 - data[4]));

	s_buffer = s_data;
	s_status = 2;
	
	SDL_PauseAudio(0);
}

uint8 DSP_GetStatus(void)
{
	return (SDL_GetAudioStatus() != 0) ? s_status : 0;
}
