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

#ifndef ___MIDI_EVENT___
#define ___MIDI_EVENT___

#ifdef __cplusplus
extern "C" {
	#endif

#include "midi_message.h"

/* MIDIEvent type definition */
typedef struct _event
{
MIDIMessage* _msg;
unsigned long _ticks;

int _is_meta;
int _is_sysex;
int _data_size;
byte* _data; /* in case of meta or sysex */

struct _event* _next;
}MIDIEvent;

/*
* Creates a new MIDIEvent.
* param: MIDIMessage* msg => a message for this event.
* param: long t => ticks ( time stamp ) for this event.
*
* returns:
* A pointer to a new MIDIEvent.
*/
MIDIEvent* create_midi_event(MIDIMessage* msg, unsigned long t);

/*
* Creates a new MIDIEvent ( meta event ).
* param: MIDIMessage* msg => a message for this event.
* param: long t => ticks ( time stamp ) for this event.
* param: int length => extra data lenth.
*
* returns:
* A pointer to a midi meta event.
*/
MIDIEvent* create_midi_meta_event(MIDIMessage* msg, unsigned long t, int data_size);

/*
* Creates a new MIDIEvent ( sysex event ).
* param: MIDIMessage* msg => a message for this event.
* param: long t => ticks ( time stamp ) for this event.
* param: int length => extra data lenth.
*
* returns:
* A pointer to a midi sysex event.
*/
MIDIEvent* create_midi_sysex_event(MIDIMessage* msg, unsigned long t, int data_size);

/*
* Clone a midi event.
* param: const MIDIEvent* event => a midi event to clone.
*
* returns:
*
* a clone of the midi event passed as parameter.
*/
MIDIEvent* clone_midi_event(const MIDIEvent* event);

/*
* Destroy a MIDIEvent.
* param: MIDIEvent* event => an event to destroy.
*/
void destroy_midi_event(MIDIEvent* event);

/*
* Function to check for short midi event.
* We can consider a midi short event a midi event just having:
* - a time stamp (ticks)
* - a short midi message:
* -- note off
* -- note on
* -- poly aftertouch
* -- control change
* -- program change
* -- channel aftertouch
* -- pitch bend
*
* param: const MIDIEvent* event => a midi event to evaluate
*
* returns:
* 1 => is a short midi event.
* 0 => is not a short midi event.
*/
int is_short_event(const MIDIEvent* event);

/*
* Function to check for tempo event.
* param: const MIDIEvent* event => a midi event to evaluate.
*
* returns:
* 1 => is a midi tempo event.
* 0 => is not a midi tempo event.
*/
int is_tempo_event(const MIDIEvent* event);

/*
* Macro to access ticks in a particular midi event.
*/
#define ticks_event(event) ((event)->_ticks)

/*
* Macro to access a midi message in a particular midi event.
*/
#define msg_event(event) ((event)->_msg)

/*
* Macro to get next event.
*/
#define next_event(event) ((event)->_next)

/*
* Macros to know if a particular event is a meta event or a sysex event.
*/
#define is_meta_event(event) ((event)->_is_meta == 1)
#define is_sysex_event(event) ((event)->_is_sysex == 1)

/*
* Macro to get the size of extra data in case of meta or sysex event.
*/
#define data_size_event(event) ((event)->_data_size)

#ifdef __cplusplus
}
#endif

#endif

