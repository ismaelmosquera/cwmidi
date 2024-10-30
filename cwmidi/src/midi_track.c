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
#include "midi_track.h"

MIDITrack* create_midi_track()
{
MIDITrack* track = (MIDITrack*)malloc(sizeof(MIDITrack));
track->_items = 0;
track->_name_length = 0;
track->_name = NULL;
track->_head = NULL;
track->_tail = NULL;
return track;
}

MIDITrack* clone_midi_track(const MIDITrack* track)
{
int i, t_items;
const MIDIEvent* it = NULL;
MIDITrack* t = NULL;
if(track == NULL) return NULL;
t = create_midi_track();
if(track->_name != NULL)
{
t->_name_length = track->_name_length;
t->_name = (char*)malloc(t->_name_length * sizeof(char));
for(i = 0; i < t->_name_length; i++) t->_name[i] = track->_name[i];
}
t_items = track->_items;
it = track->_head;
for(i = 0; i < t_items; i++)
{
add_midi_event(t, clone_midi_event(it));
it = it->_next;
}
return t;
}

void destroy_midi_track(MIDITrack* track)
{
MIDIEvent* event = NULL;
if(track == NULL) return;
while(!is_empty_track(track))
{
event = head_track(track);
head_track(track) = next_event(track->_head);
destroy_midi_event(event);
track->_items--;
}
free(track);
track = NULL;
}

void add_midi_event(MIDITrack* track, MIDIEvent* event)
{
if(track->_items == 0)
{
track->_head = event;
track->_tail = event;
}
else
{
track->_tail->_next = event;
track->_tail = event;
}
track->_items++;
}

int has_tempo_events(const MIDITrack* track)
{
	const MIDIEvent* it = NULL;
	if(track == NULL) return 0;
it = head_track(track);
while(it != NULL)
{
if(status_msg(msg_event(it)) == 0xff && data1_msg(msg_event(it)) == 0x51) return 1;
it = next_event(it);
}
return 0;
}

/* END */
