/*
 * Copyright (c) 2021-2022 Ismael Mosquera Rivera
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
#include "midi_event.h"
#include "midi_tempo.h"
#include "midi_track_merger.h"
#include "midi_file.h"
#include "midi_out.h"
#include "midi_player.h"

/*
* Type used to launch a thread properly.
*/
typedef struct
{
void (*_play_midi)();
}MIDIPlayer;

/* init a MIDIPlayer instance */
static void init_midi_player(MIDIPlayer* p, void (*func)())
{
p->_play_midi = func;
}

/* private vars */
static int _is_playing = 0;
static int _stop_requested = 0;
static MIDISong* _song = NULL;
static MIDITrack* _track = NULL;
static pthread_t _pt;
static MIDIPlayer _player;
/* end private vars */

/*
* Helper function to play a midi track.
* param: MIDITrack* track => a midi track to play.
* param: int ticksperq => division.
*/
static void play_midi_track(const MIDITrack*track, int ticksperq)
{
	int flag;
int division = ticksperq;
unsigned long tempo = 500000; /* default */
unsigned long t;
unsigned long last_ticks;
unsigned long current_ticks;
unsigned long duration; /* duration in milliseconds */
const MIDIEvent* e;

_stop_requested = 0;
/* Open the MIDI output port */
   flag = midi_out_open();
   if (!flag) return; /* error openning the midi out device */

e = head_track(track);
/* send all midi messages where ticks = 0 */
while(ticks_event(e) == 0)
{
if(is_tempo_event(e))
{
tempo = get_tempo_mu(e);
}
else
{
midi_out_write(dispatch_msg(msg_event(e)));
}
e = next_event(e);
}
last_ticks = 0;
while(e != NULL && !_stop_requested)
{
	current_ticks = ticks_event(e);
duration = ticks2milliseconds(current_ticks - last_ticks, division, tempo);
t = timeGetTime();
while((timeGetTime() - t) < duration) ;
while((e != NULL) && (ticks_event(e) == current_ticks && !_stop_requested))
{
if(is_tempo_event(e))
{
tempo = get_tempo_mu(e);
}
else
{
	midi_out_write(dispatch_msg(msg_event(e)));
}
	e = next_event(e);
}
last_ticks = current_ticks;
}
/* close all */
midi_out_close();
}

/* helper functions to launch a thread */
static void thread_code()
{
if(_song == NULL || _track == NULL) return;
stop_midi();
_is_playing = 1;
play_midi_track(_track, song_ticksperq(_song));
_is_playing = 0;
}

static void* splay_midi_thread_safe(void* ptr)
{
((MIDIPlayer*)ptr)->_play_midi();
return NULL;
}

/* end helper functions */

/* implementation */

void set_midi_out_port(int port)
{
	midi_out_dev_id(port);
}

int load_midi(const char* filename)
{
	stop_midi();
if(_song == NULL) init_midi_player(&_player, thread_code);
if(_song != NULL) destroy_midi_song(_song);
if(_track != NULL) destroy_midi_track(_track);
_song = read_midi_file(filename);
if(_song == NULL) return 0;
if(song_tracks(_song) > 1)
{
	_track = merge_midi_tracks(_song);
}
else
{
	_track = _song->_tracks[0];
}
return (_track == NULL) ? 0 : 1;
}

int play_midi()
{
	if(_is_playing) return 1;
	return pthread_create(&_pt, NULL, splay_midi_thread_safe, &_player);
}

void stop_midi()
{
/* exit playing loop */
_stop_requested = 1;
}

/* END */

