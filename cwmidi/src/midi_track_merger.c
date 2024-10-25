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

#include <stddef.h>
#include "midi_event.h"
#include "midi_track_merger.h"

/*
* Helper function to insert midi events in a midi track in time order.
*/
static void insert_midi_event(MIDITrack* track, const MIDIEvent* event)
{
	MIDIEvent* ev = NULL;
MIDIEvent* it = NULL;
if(track == NULL || event == NULL) return;
ev = clone_midi_event(event);
if(is_empty_track(track))
{
	track->_head = ev;
	track->_tail = ev;
}
else
{
	if(ev->_ticks < track->_head->_ticks)
	{
		ev->_next = track->_head;
		track->_head = ev;
	}
	else if(ev->_ticks >= track->_tail->_ticks)
	{
		track->_tail->_next = ev;
		track->_tail = ev;
	}
	else
	{
		it = head_track(track);
		while(it->_next != NULL)
		{
			if(it->_next->_ticks >= ev->_ticks)
			{
				if(is_tempo_event(it->_next) && it->_next->_ticks == ev->_ticks) it = next_event(it);
				ev->_next = it->_next;
				it->_next = ev;
				break;
			}
			it = next_event(it);
		}
	}
}
track->_items++;
}

/* end helper functions */

/* implementation */
MIDITrack* merge_midi_tracks(const MIDISong* song)
{
int i;
MIDITrack* track = NULL;
MIDIEvent* event = NULL;
if(song == NULL) return NULL;
track = create_midi_track();
for(i = 0; i < song->_ntracks; i++)
{
	event = head_track(song->_tracks[i]);
	while(event != NULL)
	{
		if(is_short_event(event) || is_tempo_event(event))
		{
insert_midi_event(track, event);
}
		event = next_event(event);
	}
}
return track;
}

/* END */


