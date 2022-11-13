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
#include "midi_message.h"

/* Defines for MIDI message status byte */
#define NOTE_OFF 0x80
#define NOTE_ON 0x90
#define POLY_AFTERTOUCH 0xa0
#define CONTROL_CHANGE 0xb0
#define PROGRAM_CHANGE 0xc0
#define CHANNEL_AFTERTOUCH 0xd0
#define PITCH_BEND 0xe0
/* end status byte defines */

/* implementation */

MIDIMessage* create_midi_message(byte status, byte data1, byte data2)
{
MIDIMessage* msg = (MIDIMessage*)malloc(sizeof(MIDIMessage));
status_msg(msg) = status;
data1_msg(msg) = data1;
data2_msg(msg) = data2;
msg->_data[3] = 0; /* unused */
return msg;
}

MIDIMessage* clone_midi_message(const MIDIMessage* msg)
{
	if(msg == NULL) return NULL;
return create_midi_message(msg->_data[0], msg->_data[1], msg->_data[2]);
}

void destroy_midi_message(MIDIMessage* msg)
{
if(msg == NULL) return;
free(msg);
msg = NULL;
}

MIDIMessage* midi_note_off(byte channel, byte pitch, byte velocity)
{
byte status = NOTE_OFF | (channel & 0x0f);
return create_midi_message(status, pitch, velocity);
}

MIDIMessage* midi_note_on(byte channel, byte pitch, byte velocity)
{
byte status = NOTE_ON | (channel & 0x0f);
return create_midi_message(status, pitch, velocity);
}

MIDIMessage* midi_poly_aftertouch(byte channel, byte pitch, byte pressure)
{
byte status = POLY_AFTERTOUCH | (channel & 0x0f);
return create_midi_message(status, pitch, pressure);
}

MIDIMessage* midi_control_change(byte channel, byte control_type, byte value)
{
byte status = CONTROL_CHANGE | (channel & 0x0f);
return create_midi_message(status, control_type, value);
}

MIDIMessage* midi_program_change(byte channel, byte program)
{
byte status = PROGRAM_CHANGE | (channel & 0x0f);
return create_midi_message(status, program, 0);
}

MIDIMessage* midi_channel_aftertouch(byte channel, byte pressure)
{
	byte status = CHANNEL_AFTERTOUCH | (channel & 0x0f);
	return create_midi_message(status, pressure, 0);
}

MIDIMessage* midi_pitch_bend(byte channel, byte msbyte, byte lsbyte)
{
byte status = PITCH_BEND | (channel & 0x0f);
return create_midi_message(status, msbyte, lsbyte);
}

/* END */
