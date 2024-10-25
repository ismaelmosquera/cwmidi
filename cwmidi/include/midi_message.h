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

#ifndef ___MIDI_MESSAGE___
#define ___MIDI_MESSAGE___

#ifdef __cplusplus
extern "C"{
	#endif

/* byte type definition */
typedef unsigned char byte;

/* MIDIMessage type definition */
typedef union
{
	unsigned long _dispatch; /* packd message */
byte _data[4];
}MIDIMessage;

/*
* Creates a new MIDIMessage.
* param: byte status => status byte.
* param: byte data1 => data1 byte.
* param: data2 => data2 byte.
*
* A MIDIMessage can be 3 bytes long as much.
* The bytes not used in a message are not taken in account.
*
* returns:
* A pointer to a new MIDIMessage.
*/
MIDIMessage* create_midi_message(byte status, byte data1, byte data2);

/*
* Clone a midi message.
* param: const MIDIMessage* msg => midi message to clone.
*
* returns:
*
* a clone midi message from the one passed as parameter.
*/
MIDIMessage* clone_midi_message(const MIDIMessage* msg);

/*
* Destroy a MIDIMessage.
* param: MIDIMessage* msg => a pointer to a message to destroy.
*/
void destroy_midi_message(MIDIMessage* msg);

/*
* Gets a midi note off message.
* param: byte channel.
* param: byte pitch.
* param: byte velocity.
*
* returns:
*A midi note off message.
*/
MIDIMessage* midi_note_off(byte channel, byte pitch, byte velocity);

/*
* Gets a midi note on message.
* param: byte channel.
* param: byte pitch.
* param: byte velocity.
*
* returns:
* A midi note on message.
*/
MIDIMessage* midi_note_on(byte channel, byte pitch, byte velocity);

/*
* Gets a midi poly aftertouch message.
* param: byte channel.
* param: byte pitch.
* param: byte pressure.
*
* returns:
* A midi poly aftertouch message.
*/
MIDIMessage* midi_poly_aftertouch(byte channel, byte pitch, byte pressure);

/*
* Gets a midi control change message.
* param: byte channel.
* param: byte control_type.
* param: value.
*
* returns:
* A midi control change message.
*/
MIDIMessage* midi_control_change(byte channel, byte control_type, byte value);

/*
* Gets a midi program change message.
* param: byte channel.
* param: byte program.
*
* returns:
* A midi program change message.
*/
MIDIMessage* midi_program_change(byte channel, byte program);

/*
* Gets a midi channel aftertouch message.
* param: byte channel.
* param: byte pressure.
*
* returns:
* A midi channel aftertouch message.
*/
MIDIMessage* midi_channel_aftertouch(byte channel, byte pressure);

/*
* Gets a pitch bend message.
* param: byte channel.
* param: byte msbyte.
* param: byte lsbyte.
*
* returns:
* A pitch bend message.
*/
MIDIMessage* midi_pitch_bend(byte channel, byte msbyte, byte lsbyte);

/*
* Macros to access midi message data.
*/
#define status_msg(msg) ((msg)->_data[0])
#define data1_msg(msg) ((msg)->_data[1])
#define data2_msg(msg) ((msg)->_data[2])

/*
* Macro to dispatch a midi message
*/
#define dispatch_msg(msg) ((msg)->_dispatch)

#ifdef __cplusplus
}
	#endif

#endif
