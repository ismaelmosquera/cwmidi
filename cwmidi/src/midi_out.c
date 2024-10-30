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

#include <windows.h>
#include <mmsystem.h>
#include "midi_out.h"


/* MIDI out device ID */
static int _devID = 0;

/* MIDI device interface for sending MIDI output */
static HMIDIOUT dev;

/* implementation */

void midi_out_dev_id(int id)
{
_devID = id;
}

int midi_out_open()
{
	int flag = midiOutOpen(&dev, _devID, 0, 0, CALLBACK_NULL);
	   return (flag != MMSYSERR_NOERROR) ? 0 : 1; // manage error openning the midi out device
}

void midi_out_write(unsigned long msg)
{
midiOutShortMsg(dev, msg);
}

void midi_out_close()
{
midiOutReset(dev);
midiOutClose(dev);
}


/* END */
