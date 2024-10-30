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

#include <stdlib.h>
#include "midi_event.h"

MIDIEvent* create_midi_event(MIDIMessage* msg, unsigned long t)
{
MIDIEvent* event = (MIDIEvent*)malloc(sizeof(MIDIEvent));
event->_msg = msg;
event->_ticks = t;
event->_is_meta = 0;
event->_is_sysex = 0;
event->_data_size = 0;
event->_data = NULL;
event->_next = NULL;
return event;
}

MIDIEvent* create_midi_meta_event(MIDIMessage* msg, unsigned long t, int data_size)
{
MIDIEvent* event = create_midi_event(msg, t);
event->_is_meta = 1;
event->_data_size = data_size;
event->_data = (byte*)malloc(event->_data_size * sizeof(byte));
return event;
}

MIDIEvent* create_midi_sysex_event(MIDIMessage* msg, unsigned long t, int data_size)
{
MIDIEvent* event = create_midi_event(msg, t);
event->_is_sysex = 1;
event->_data_size = data_size;
event->_data = (byte*)malloc(event->_data_size * sizeof(byte));
return event;
}

MIDIEvent* clone_midi_event(const MIDIEvent* event)
{
	int i, flag = 0;
MIDIEvent* ev = NULL;
if(event == NULL) return NULL;
if(event->_is_meta || event->_is_sysex) flag = 1;
if(event->_is_meta)
{
	ev = create_midi_meta_event(clone_midi_message(event->_msg), event->_ticks, event->_data_size);
}
else if(event->_is_sysex)
{
	ev = create_midi_sysex_event(clone_midi_message(event->_msg), event->_ticks, event->_data_size);
}
else
{
ev = create_midi_event(clone_midi_message(event->_msg), event->_ticks);
}
if(flag)
{
	for(i = 0; i < ev->_data_size; i++) ev->_data[i] = event->_data[i];
}
return ev;
}

void destroy_midi_event(MIDIEvent* event)
{
if(event == NULL) return;
if(event->_msg != NULL) destroy_midi_message(event->_msg);
event->_msg = NULL;
if(event->_data != NULL) free(event->_data);
event->_data = NULL;
free(event);
event = NULL;
}

int is_short_event(const MIDIEvent* event)
{
if(event == NULL) return 0;
return (!event->_is_meta && !event->_is_sysex) ? 1 : 0;
}

int is_tempo_event(const MIDIEvent* event)
{
if(event == NULL) return 0;
return (event->_msg->_data[0]==0xff && event->_msg->_data[1]==0x51) ? 1 : 0;
}

/* END */
