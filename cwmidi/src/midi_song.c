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
#include "midi_song.h"

MIDISong* create_midi_song(int ticksperq, int ntracks)
{
	int i;
MIDISong* song = (MIDISong*)malloc(sizeof(MIDISong));
song->_ticksperq = ticksperq;
song->_ntracks = ntracks;
song->_tracks = (MIDITrack**)malloc(song_tracks(song) * sizeof(MIDITrack*));
for(i = 0; i < song->_ntracks; i++) song->_tracks[i] = NULL;
return song;
}

MIDISong* clone_midi_song(const MIDISong* song)
{
int n;
MIDISong* s = NULL;
if(song == NULL) return NULL;
s = create_midi_song(song->_ticksperq, song->_ntracks);
for(n = 0; n < s->_ntracks; n++) s->_tracks[n] = clone_midi_track(song->_tracks[n]);
return s;
}

void destroy_midi_song(MIDISong* song)
{
int i;
if(song == NULL) return;
for(i = 0; i < song_tracks(song); i++)
{
destroy_midi_track(song->_tracks[i]);
}
free(song);
song = NULL;
}

/* END */
