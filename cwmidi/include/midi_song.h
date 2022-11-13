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

#ifndef ___MIDI_SONG___
#define ___MIDI_SONG___

#ifdef __cplusplus
extern "C" {
#endif

#include "midi_track.h"

/* MIDISong type definition */
typedef struct
{
int _ticksperq;
int _ntracks;
MIDITrack** _tracks;
}MIDISong;

/*
* Creates a new MIDISong.
* param: int ticksperq => ticks per q for this midi song.
* param: int ntracks => number of tracks for this midi song.
*
* returns:
* A pointer to a new created midi song.
*/
MIDISong* create_midi_song(int ticksperq, int ntracks);

/*
* Clone a midi song.
* param: const MIDISong* song => a midi song to clone.
*
* returns:
* a clone of the midi song passed as parameter.
*/
MIDISong* clone_midi_song(const MIDISong* song);

/*
* Destroy a MIDISong.
* param: MIDISong* song => a pointer to a midi song to destroy.
*/
void destroy_midi_song(MIDISong* song);

/*
* Macro to access the ticks per q in a midi song.
*/
#define song_ticksperq(song) ((song)->_ticksperq)

/*
* Macro to access the number of tracks in a midi song.
*/
#define song_tracks(song) ((song)->_ntracks)

#ifdef __cplusplus
}
#endif

#endif
