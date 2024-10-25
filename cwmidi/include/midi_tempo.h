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

#ifndef ___MIDI_TEMPO_H___
#define ___MIDI_TEMPO_H___

#ifdef __cplusplus
extern "C" {
	#endif

#include "midi_event.h"

/*
* Gets the tempo in microseconds per quarter note (mUsPerQ) from a tempo event.
* A tempo event has a midi message: status byte = 0xff and data1 byte = 0x51
* So, a tempo event is a midi meta event.
* A midi meta event has extra data. In this case there are 3 extra data bytes.
* param: const MIDIEvent* meta => a midi meta event.
*
* returns:
* - 0 if the parameter is not a tempo event.
* - Tempo in mUsPerQ.
*/
unsigned long get_tempo_mu(const MIDIEvent* meta);

/*
* convert ticks to milliseconds.
* param: unsigned long ticks => number of ticks to convert
* param: int division => ticksperQ
* param: unsigned long tempo => tempo in mUsPerQ
*
* returns:
* Time in milliseconds
*/
unsigned long ticks2milliseconds(unsigned long ticks, int division, unsigned long tempo);

#ifdef __cplusplus
}
#endif

#endif
