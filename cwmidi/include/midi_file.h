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

#ifndef ___MIDI_FILE___
#define ___MIDI_FILE___

#ifdef __cplusplus
extern "C" {
	#endif

#include "midi_song.h"

/*
* Loads a midi song from a midi file.
* param: const char* filename => path to a midi file to load.
*
* returns:
* A pointer to a midi song with the data loaded from a midi file.
*/
MIDISong* read_midi_file(const char* filename);

/*
* Stores a midi file from the data in a midi song.
* param: const char* filename => file name to store.
* param: MIDISong* song => midi song to store.
*
* returns:
* 1 => success.
* 0 => failed.
*/
int write_midi_file(const char* filename, const MIDISong* song);

#ifdef __cplusplus
}
#endif

#endif
