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

#ifndef ___MIDI_PLAYER_H___
#define ___MIDI_PLAYER_H___

#ifdef __cplusplus
extern "C" {
#endif

/*
* Gets description of the MIDI out devices availabel in your system.
*
* returns:
* ( by reference ) => number of midi out devices in your system.
* An array of strings with info about your MIDI out devices.
*/
char** get_midi_out_devs(int* numdevs);

/*
* Set MIDI out port.
* param: int port => MIDI out port id.
* The id of the port must be in the range 0 .. #devices-1
*/
void set_midi_out_port(int port);

/*
* Loads midi from a standard midi file ( smf )
* param: const char* filename => path to a midi file
*
* returns:
* 0 => failed
* 1 => success
*/
int load_midi(const char* filename);

/*
* Play midi.
* Plays a midi song previously loaded
*
* returns:
* 0 => success.
* otherwise => failed.
*/
int play_midi();

/*
* Stop playing midi
*/
void stop_midi();

#ifdef __cplusplus
}
#endif

#endif
