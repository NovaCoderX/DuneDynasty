/** @file src/timer.c Timer routines. */

#include <stdlib.h>

#include <time.h>

#include "types.h"
#include "os/sleep.h"
#include "os/error.h"

#include "timer.h"



volatile uint32 g_timerGUI = 0;                                      /*!< Tick counter. Increases with 1 every tick when Timer 1 is enabled. Used for GUI. */
volatile uint32 g_timerGame = 0;                                     /*!< Tick counter. Increases with 1 every tick when Timer 2 is enabled. Used for game timing (units, ..). */
volatile uint32 g_timerInput = 0;                                    /*!< Tick counter. Increases with 1 every tick. Used for input timing. */
volatile uint32 g_timerSleep = 0;                                    /*!< Tick counter. Increases with 1 every tick. Used for sleeping. */
volatile uint32 g_timerTimeout = 0;                                  /*!< Tick counter. Decreases with 1 every tick when non-zero. Used to timeout. */

static uint16 s_timersActive = 0;


typedef struct TimerNode {
	uint32 usec_left;
	uint32 usec_delay;
	void (*callback)(void);
	bool callonce;
} TimerNode;



static TimerNode *s_timerNodes = NULL;
static int s_timerNodeCount = 0;
static int s_timerNodeSize  = 0;

static uint32 s_timerLastTime;


uint32 Timer_GetTime(void)
{
	return clock() * 1000 / CLOCKS_PER_SEC;
}

/**
 * Run the timer interrupt handler.
 */
static void Timer_InterruptRun(int arg)
{
	TimerNode *node;
	uint32 new_time, usec_delta, delta;
	int i;

	/* Lock the timer, to avoid double-calls */
	static bool timerLock = false;
	if (timerLock) return;
	timerLock = true;

	/* Calculate the time between calls */
	new_time   = Timer_GetTime();
	usec_delta = (new_time - s_timerLastTime) * 1000;
	s_timerLastTime = new_time;

	/* Walk all our timers, see which (and how often) it should be triggered */
	node = s_timerNodes;
	for (i = 0; i < s_timerNodeCount; i++, node++) {
		delta = usec_delta;

		/* No delay means: as often as possible, but don't worry about it */
		if (node->usec_delay == 0) {
			node->callback();
			continue;
		}

		if (node->callonce) {
			if (node->usec_left <= delta) {
				delta -= node->usec_left;
				node->usec_left = node->usec_delay;
				if(arg == 0) node->callback();
				while (node->usec_left <= delta) delta -= node->usec_left;
			}
		} else while (node->usec_left <= delta) {
			delta -= node->usec_left;
			node->usec_left = node->usec_delay;
			node->callback();
		}
		node->usec_left -= delta;
	}

	timerLock = false;
}


void SleepAndProcessBackgroundTasks(void)
{
	Timer_InterruptRun(0);
}





/**
 * Initialize the timer.
 */
void Timer_Init(void)
{
	s_timerLastTime = Timer_GetTime();
}

/**
 * Uninitialize the timer.
 */
void Timer_Uninit(void)
{
	free(s_timerNodes); s_timerNodes = NULL;
	s_timerNodeCount = 0;
	s_timerNodeSize = 0;
}

/**
 * Add a timer.
 * @param callback the callback for the timer.
 * @param usec_delay The interval of the timer.
 */
void Timer_Add(void (*callback)(void), uint32 usec_delay, bool callonce)
{
	TimerNode *node;
	if (s_timerNodeCount == s_timerNodeSize) {
		s_timerNodeSize += 2;
		s_timerNodes = (TimerNode *)realloc(s_timerNodes, s_timerNodeSize * sizeof(TimerNode));
	}
	node = &s_timerNodes[s_timerNodeCount++];

	node->usec_left  = usec_delay;
	node->usec_delay = usec_delay;
	node->callback   = callback;
	node->callonce   = callonce;
}

/**
 * Change the interval of a timer.
 * @param callback The callback to change the timer of.
 * @param usec_delay The interval.
 */
void Timer_Change(void (*callback)(void), uint32 usec_delay)
{
	int i;
	TimerNode *node = s_timerNodes;
	for (i = 0; i < s_timerNodeCount; i++, node++) {
		if (node->callback == callback) {
			node->usec_delay = usec_delay;
			return;
		}
	}
}

/**
 * Remove a timer from the queue.
 * @param callback Which callback to remove.
 */
void Timer_Remove(void (*callback)(void))
{
	int i;
	TimerNode *node = s_timerNodes;
	for (i = 0; i < s_timerNodeCount; i++, node++) {
		if (node->callback == callback) {
			*node = s_timerNodes[--s_timerNodeCount];
			return;
		}
	}
}

/**
 * Handle game timers.
 */
void Timer_Tick(void)
{
	if ((s_timersActive & TIMER_GUI)  != 0) g_timerGUI++;
	if ((s_timersActive & TIMER_GAME) != 0) g_timerGame++;
	g_timerInput++;
	g_timerSleep++;

	if (g_timerTimeout != 0) g_timerTimeout--;
}

/**
 * Set timers on and off.
 *
 * @param timer The timer to switch.
 * @param set True sets the timer on, false sets it off.
 * @return True if timer was set, false if it was not set.
 */
bool Timer_SetTimer(TimerType timer, bool set)
{
	uint8 t;
	bool ret;

	t = (1 << (timer - 1));
	ret = (s_timersActive & t) != 0;

	if (set) {
		s_timersActive |= t;
	} else {
		s_timersActive &= ~t;
	}

	return ret;
}

/**
 * Sleep for an amount of ticks.
 * @param ticks The amount of ticks to sleep.
 */
void Timer_Sleep(uint16 ticks)
{
	uint32 tick = g_timerSleep + ticks;
	while (tick >= g_timerSleep) sleepIdle();
}
