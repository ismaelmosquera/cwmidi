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

#ifndef ___MIDI_OUT_DEV_LIST___
#define ___MIDI_OUT_DEV_LIST___

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
* Lists the available MIDI out devices in your system.
* param: dev_list -> array of char containing a list of the available devices.
* param: ndevs -> number of MIDI out devices in your system.
*
*/
void list_midi_out_devs(char** dev_list, int ndevs);


#ifdef __cplusplus
}
#endif

#endif
