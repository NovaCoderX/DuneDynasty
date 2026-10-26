/* Audio addon: allegro_audio.h. */

#include "allegro5/allegro.h"
#include "allegro5/allegro_audio.h"
#include "a5_stub.h"

bool al_install_audio(void)
{
   A5_STUB();
   return false;
}

void al_uninstall_audio(void)
{
   A5_STUB();
}

/* Real implementation, as in Allegro's audio.c. */
size_t al_get_audio_depth_size(ALLEGRO_AUDIO_DEPTH depth)
{
   switch (depth) {
      case ALLEGRO_AUDIO_DEPTH_INT8:
      case ALLEGRO_AUDIO_DEPTH_UINT8:
         return sizeof(int8_t);
      case ALLEGRO_AUDIO_DEPTH_INT16:
      case ALLEGRO_AUDIO_DEPTH_UINT16:
         return sizeof(int16_t);
      case ALLEGRO_AUDIO_DEPTH_INT24:
      case ALLEGRO_AUDIO_DEPTH_UINT24:
         return sizeof(int32_t);
      case ALLEGRO_AUDIO_DEPTH_FLOAT32:
         return sizeof(float);
      default:
         return 0;
   }
}

/* Voices and mixers. */

ALLEGRO_VOICE *al_create_voice(unsigned int freq,
   ALLEGRO_AUDIO_DEPTH depth, ALLEGRO_CHANNEL_CONF chan_conf)
{
   A5_STUB();
   return NULL;
}

void al_destroy_voice(ALLEGRO_VOICE *voice)
{
   A5_STUB();
}

ALLEGRO_MIXER *al_create_mixer(unsigned int freq,
   ALLEGRO_AUDIO_DEPTH depth, ALLEGRO_CHANNEL_CONF chan_conf)
{
   A5_STUB();
   return NULL;
}

void al_destroy_mixer(ALLEGRO_MIXER *mixer)
{
   A5_STUB();
}

bool al_attach_mixer_to_voice(ALLEGRO_MIXER *mixer, ALLEGRO_VOICE *voice)
{
   A5_STUB();
   return false;
}

/* Samples. */

ALLEGRO_SAMPLE *al_create_sample(void *buf, unsigned int samples,
   unsigned int freq, ALLEGRO_AUDIO_DEPTH depth,
   ALLEGRO_CHANNEL_CONF chan_conf, bool free_buf)
{
   A5_STUB();
   return NULL;
}

void al_destroy_sample(ALLEGRO_SAMPLE *spl)
{
   A5_STUB();
}

ALLEGRO_SAMPLE_INSTANCE *al_create_sample_instance(ALLEGRO_SAMPLE *data)
{
   A5_STUB();
   return NULL;
}

void al_destroy_sample_instance(ALLEGRO_SAMPLE_INSTANCE *spl)
{
   A5_STUB();
}

bool al_set_sample(ALLEGRO_SAMPLE_INSTANCE *spl, ALLEGRO_SAMPLE *data)
{
   A5_STUB();
   return false;
}

bool al_attach_sample_instance_to_mixer(ALLEGRO_SAMPLE_INSTANCE *stream,
   ALLEGRO_MIXER *mixer)
{
   A5_STUB();
   return false;
}

bool al_play_sample_instance(ALLEGRO_SAMPLE_INSTANCE *spl)
{
   A5_STUB();
   return false;
}

bool al_get_sample_instance_playing(const ALLEGRO_SAMPLE_INSTANCE *spl)
{
   A5_STUB();
   return false;
}

bool al_set_sample_instance_gain(ALLEGRO_SAMPLE_INSTANCE *spl, float val)
{
   A5_STUB();
   return false;
}

bool al_set_sample_instance_pan(ALLEGRO_SAMPLE_INSTANCE *spl, float val)
{
   A5_STUB();
   return false;
}

/* Audio streams. */

ALLEGRO_AUDIO_STREAM *al_create_audio_stream(size_t buffer_count,
   unsigned int samples, unsigned int freq,
   ALLEGRO_AUDIO_DEPTH depth, ALLEGRO_CHANNEL_CONF chan_conf)
{
   A5_STUB();
   return NULL;
}

ALLEGRO_AUDIO_STREAM *al_load_audio_stream(const char *filename,
   size_t buffer_count, unsigned int samples)
{
   A5_STUB();
   return NULL;
}

void al_destroy_audio_stream(ALLEGRO_AUDIO_STREAM *stream)
{
   A5_STUB();
}

bool al_attach_audio_stream_to_mixer(ALLEGRO_AUDIO_STREAM *stream,
   ALLEGRO_MIXER *mixer)
{
   A5_STUB();
   return false;
}

bool al_detach_audio_stream(ALLEGRO_AUDIO_STREAM *stream)
{
   A5_STUB();
   return false;
}

ALLEGRO_EVENT_SOURCE *al_get_audio_stream_event_source(
   ALLEGRO_AUDIO_STREAM *stream)
{
   A5_STUB();
   return NULL;
}

void *al_get_audio_stream_fragment(const ALLEGRO_AUDIO_STREAM *stream)
{
   A5_STUB();
   return NULL;
}

bool al_set_audio_stream_fragment(ALLEGRO_AUDIO_STREAM *stream, void *val)
{
   A5_STUB();
   return false;
}

bool al_get_audio_stream_playing(const ALLEGRO_AUDIO_STREAM *spl)
{
   A5_STUB();
   return false;
}

bool al_set_audio_stream_gain(ALLEGRO_AUDIO_STREAM *stream, float val)
{
   A5_STUB();
   return false;
}

bool al_set_audio_stream_pan(ALLEGRO_AUDIO_STREAM *stream, float val)
{
   A5_STUB();
   return false;
}
