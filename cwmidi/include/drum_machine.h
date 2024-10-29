/*
 * Copyright (c) 2024 Ismael Mosquera Rivera
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

#ifndef ___DRUM_MACHINE___
#define ___DRUM_MACHINE___

#ifdef __cplusplus
extern "C"{
	#endif

/*
* This header atempts to promote functions to simulate a drum machine
*/

/*
* Sets output filename.
* If you do not set a filename, it will be save as "out.mid" by default.
* param: filename - filename to store your simulation in a MIDI file.
*
*/
void set_output_filename(const char* filename);

 /*
* Set MIDI out ID.
* param: int id => MIDI out port id.
* The id of the port must be in the range 0 .. #devices-1
*/
void set_midi_out_id(int id);

/*
* Starts a drum machine simulation.
*
* returns: 0-> success or failed otherwise.
*/
int start_drum_machine();

/*
* Stops a drum machine simulation.
* Afterwards, the current simulation is stored in a MIDI file with the previously set name or with the default one.
*/
void stop_drum_machine();

#ifdef __cplusplus
}
	#endif

#endif
