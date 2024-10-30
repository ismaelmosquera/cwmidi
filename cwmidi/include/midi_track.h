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

#ifndef ___MIDI_TRACK___
#define ___MIDI_TRACK___

#ifdef __cplusplus
extern "C" {
	#endif

#include "midi_event.h"

/* MIDITrack type definition */
typedef struct
{
	int _items;
int _name_length;
char* _name;
MIDIEvent* _head;
MIDIEvent* _tail;
}MIDITrack;

/*
* Creates a new MIDITrack.
*
* returns:
* A pointer to a MIDITrack.
*/
MIDITrack* create_midi_track();

/*
* Clone a midi track.
* param: const MIDITrack* track => a midi track to clone.
*
* returns:
* a clone of the midi track passed as parameter.
*/
MIDITrack* clone_midi_track(const MIDITrack* track);

/*
* Destroy a MIDITrack.
* param: MIDITrack* track => a midi track to destroy.
*/
void destroy_midi_track(MIDITrack* track);

/*
* Adds a new MIDIEvent to a MIDITrack.
* param: MIDITrack* track => midi track to add a midi event.
* param: MIDIEvent* event => midi event to add.
*/
void add_midi_event(MIDITrack* track, MIDIEvent* event);

/*
* Check for tempo events in a MIDITrack.
* param: const MIDITrack* track => track to look for tempo events.
*
* returns:
* 0 => tempo events not found.
* 1 => tempo events found.
*/
int has_tempo_events(const MIDITrack* track);

/*
* Macro to get the first event from a track.
*/
#define head_track(track) ((track)->_head)

/*
* Macro to check for empty midi track.
*/
#define is_empty_track(track) ((track)->_items == 0)

#ifdef __cplusplus
}
#endif

#endif

