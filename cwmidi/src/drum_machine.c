/*
 * Copyright (c) 2024 Ismael Mosquera Rivera
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include <windows.h>
#include <mmsystem.h>
#include <stdlib.h>
#include <pthread.h>
#include "midi_out.h"
#include "midi_message.h"
#include "rand.h"
#include "drum_machine.h"


/*
* Type used to launch a thread properly.
*/
typedef struct
{
void (*_start_simulation)();
}DrumMachine;

/* init a DrumMachine instance */
static void init_midi_player(DrumMachine* p, void (*func)())
{
p->_start_simulation = func;
}

/* Symbolic constants */
#define MIN_DRUM_ID 35
#define MAX_DRUM_ID 81
#define MIN_REPS 1
#define MAX_REPS 4

/* private vars */
static int _initialized = 0;
static int _is_playing = 0;
static int _stop_requested = 0;
static int _duration[10] = {100, 200, 300, 400, 500, 400, 300, 200, 100, 1000}; /* vector of durations */
static int _velocity[4] = {90, 100, 110, 120};
static int _steps[4] = {20, 30, 40, 50};
static pthread_t _pt;
static DrumMachine _player;
/* end private vars */

/* private functions */

static byte get_drum_id()
{
return (byte)random(MIN_DRUM_ID, MAX_DRUM_ID);
}

static int get_num_reps()
{
return random(MIN_REPS, MAX_REPS);
}

static byte get_velocity()
{
int index = random(0, 3);
return (byte)_velocity[index];
}

static unsigned get_duration()
{
int index = random(0, 9);
return (unsigned)_duration[index];
}

static unsigned get_step()
{
int index = random(0, 3);
return (unsigned)_steps[index];
}

static int add_silence()
{
	int n = random(1, 1000);
	return (n%2 == 0) ? 1 : 0;
}

/* end private functions */

/*
* simulation function
*/
void drum_machine_simulation()
{
	int flag, i, n;
unsigned duration, current_time, step;
MIDIMessage* midi_note = NULL;

/* Open the MIDI output port */
   flag = midi_out_open();
   if (!flag) return; /* error openning the midi out device */
/* get a MIDIMessage instance */
midi_note = midi_note_on(0x09, 0, 0);

/* start simulation */
_stop_requested = 0;
/* init random process */
randomize();
step = get_duration();
while(!_stop_requested)
{
 data1_msg(midi_note )= get_drum_id();
n = get_num_reps();
for(i = 0; i < n; i++)
{
if(_stop_requested) break;
data2_msg(midi_note) = get_velocity(); /* note on */
duration = get_duration();
current_time = timeGetTime();
while((timeGetTime() - current_time) < step) ;
/* send message note on to midi out device */
midi_out_write(dispatch_msg(midi_note));
current_time = timeGetTime();
while((timeGetTime() - current_time) < duration) ;
data2_msg(midi_note) = 0; /* note off */
/* send message note off to midi out device */
midi_out_write(dispatch_msg(midi_note));
step = get_step();
}
if(add_silence())
{
step += get_duration();
}
}
/* close MIDI device */
midi_out_close();
/* free previously allocated memory */
destroy_midi_message(midi_note);
}

/* helper functions to launch a thread */
static void thread_code()
{
stop_drum_machine();
_is_playing = 1;
drum_machine_simulation();
_is_playing = 0;
}

static void* splay_midi_thread_safe(void* ptr)
{
((DrumMachine*)ptr)->_start_simulation();
return NULL;
}

/* end helper functions */


/* implementation */

void set_midi_out_id(int id)
{
	midi_out_dev_id(id);
}

int start_drum_machine()
{
	if(!_initialized)
	{
		init_midi_player(&_player, thread_code);
_initialized = 1;
	}
	if(_is_playing) return 1;
	return pthread_create(&_pt, NULL, splay_midi_thread_safe, &_player);
}

void stop_drum_machine()
{
/* exit playing loop */
_stop_requested = 1;
}


/* END */
