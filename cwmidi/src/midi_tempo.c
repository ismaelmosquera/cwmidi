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
#include <math.h>
#include "midi_tempo.h"

unsigned long get_tempo_mu(const MIDIEvent* meta)
{
unsigned long mUsperQ = 0;
if(meta == NULL) return 0;
if(!is_tempo_event(meta)) return 0;
mUsperQ |= (meta->_data[0]<<16 | meta->_data[1]<<8 | meta->_data[2]);
return mUsperQ;
}

unsigned long ticks2milliseconds(unsigned long ticks, int division, unsigned long tempo)
{
return (unsigned long)round((double)ticks*((double)tempo/(double)division)/1000.0);
}

/* END */

