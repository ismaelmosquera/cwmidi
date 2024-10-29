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

#ifndef ___MIDI_OUT___
#define ___MIDI_OUT___

#ifdef __cplusplus
extern "C"{
	#endif

/*
* In this header, there are functions to open, write and close a MIDI system device.
* /

/* public interface */

/*
* Sets a MidiOut device ID.
* param: id -> device ID.
*
* It must be in the range [0 .. n-1]
* where n is the number of MIDI out devices in your system.
*
*/
void midi_out_dev_id(int id);

/*
* Opens a MidiOut device.
* You must call this function before start writting data to the device.
*
* returns 1 if success or 0 otherwise.
*
*/
int midi_out_open();

/*
* Writes data to an already open MIDI out device.
* param: msg -> MIDI mesage to send.
*/
void midi_out_write(unsigned long msg);

/*
* Closes an already open MIDI out device.
*/
void midi_out_close();

#ifdef __cplusplus
}
	#endif

#endif
