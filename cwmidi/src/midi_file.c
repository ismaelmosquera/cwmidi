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

#include <stdio.h>
#include <stdlib.h>
#include "midi_message.h"
#include "midi_event.h"
#include "midi_track.h"
#include "midi_file.h"

/*
* Helper functions to read a standard midi file.
*/

/* global vars. */
static FILE* pfread = NULL;
static int _bytes_read = 0;
static const char __MThd__[] = {'M','T','h','d'};
static const char __MTrk__[] = {'M','T','r','k'};

typedef struct
{
byte _data[4];
}MIDIChunkType;

static MIDIChunkType* create_midi_chunk_type(byte bytes[4])
{
int i;
MIDIChunkType* chunk_type = (MIDIChunkType*)malloc(sizeof(MIDIChunkType));
for(i = 0; i < 4; i++) chunk_type->_data[i] = bytes[i];
return chunk_type;
}

static void destroy_midi_chunk_type(MIDIChunkType* chunk_type)
{
if(chunk_type == NULL) return;
free(chunk_type);
chunk_type = NULL;
}

static int equals_chunk_type(const MIDIChunkType* chunk_type, const char* str)
{
int i;
if(chunk_type == NULL || str == NULL) return 0;
for(i = 0; i < 4; i++)
{
if(chunk_type->_data[i] != str[i]) return 0;
}
return 1;
}

static void init_fread_global_vars()
{
pfread = NULL;
_bytes_read = 0;
}

static byte get_byte()
{
_bytes_read++;
return fgetc(pfread);
}

static unsigned int get_int()
{
unsigned int val;
val = get_byte();
val <<= 8;
val |= get_byte();
val <<= 8;
val |= get_byte();
val <<= 8;
val |= get_byte();
return val;
}

static unsigned short get_short()
{
unsigned short val;
val = get_byte();
val <<= 8;
val |= get_byte();
return val;
}

static MIDIChunkType* get_midi_chunk_type()
{
int i;
byte bytes[4];
for(i = 0; i < 4; i++) bytes[i] = get_byte();
return create_midi_chunk_type(bytes);
}

static unsigned int get_var_len()
{
unsigned int ret = 0;
byte tmp;
tmp = get_byte();
ret = tmp & 0x7f;
while(tmp & 0x80)
{
tmp = get_byte();
ret <<= 7;
ret |= (tmp & 0x7f);
}
return ret;
}

static void get_track_name(MIDITrack* track, const byte* ptr, int len)
{
	int i;
	if(track->_name != NULL)
	{
	free(track->_name);
	track->_name = NULL;
	}
	track->_name_length = len;
track->_name = (char*)malloc((len+1) * sizeof(char));
for(i = 0; i < len; i++) track->_name[i] = ptr[i];
track->_name[len] = '\0';
}

/* end helper read functions. */

/*
* Helper functions to write a standard midi file.
*/

/* global vars. */
static FILE* pfwrite = NULL;
static long _bytes_written = 0;
static int _ntracks = 0;
static int _format = 0;
static int _division = 0;
#define MThd 0x4d546864
#define MTrk 0x4d54726b

static void init_fwrite_global_vars()
{
pfwrite = NULL;
_bytes_written = 0;
_ntracks = 0;
_format = 0;
_division = 0;
}

static void write_char(char c)
{
fputc(c, pfwrite);
_bytes_written++;
}

static void write_32bit(unsigned long data)
{
write_char((unsigned)((data >> 24) & 0xff));
		write_char((unsigned)((data >> 16) & 0xff));
		write_char((unsigned)((data >> 8 ) & 0xff));
		write_char((unsigned)(data & 0xff));
}

static void write_16bit(int data)
{
write_char((unsigned)((data & 0xff00) >> 8));
		write_char((unsigned)(data & 0xff));
	}

static void write_header()
{
unsigned long id = MThd;
write_32bit(id);
write_32bit(6);
write_16bit(_format);
write_16bit(_ntracks);
write_16bit(_division);
}

static void write_var_len(register unsigned long value)
{
register unsigned long buffer;
		buffer = value & 0x7F;

		while( (value >>= 7) )
		{
			buffer <<= 8;
			buffer |= ((value & 0x7F) | 0x80);
		}

		while(1)
		{
			write_char(buffer);
			if (buffer & 0x80)
				buffer >>= 8;
			else
				break;
		}
}

/* end write helper functions. */

MIDISong* read_midi_file(const char* filename)
{
	int i, j;
	byte b, b1, b2;
	byte running_status;
	byte meta_type;
	unsigned long t; /* ticks */
unsigned int dt; /* delta time */
int type;
unsigned int length;
unsigned short format, ntracks;
int ticksperq;
int midi_chunk_length;
MIDIChunkType* chunk_type = NULL;
MIDIEvent* meta_event = NULL;
MIDIEvent* sysex_event = NULL;
MIDITrack* track = NULL;
MIDISong* song = NULL;
static int bytes_per_msg[7] = {3, 3, 3, 3, 2, 3, 3};

init_fread_global_vars();
pfread = fopen(filename, "rb");
if(pfread == NULL) return NULL;

chunk_type = get_midi_chunk_type();
if(!equals_chunk_type(chunk_type, __MThd__)) return NULL;
length = get_int();
if(length != 6) return NULL;
format = get_short();
if(format != 0 && format != 1) return NULL;
ntracks = get_short();
ticksperq = get_short();
song = create_midi_song(ticksperq, ntracks);
for(i = 0; i < song_tracks(song); i++)
{
	destroy_midi_chunk_type(chunk_type);
chunk_type = get_midi_chunk_type();
if(!equals_chunk_type(chunk_type, __MTrk__)) return NULL;
midi_chunk_length = get_int();
running_status = 0;
t = 0;
track = create_midi_track();
_bytes_read = 0;
while(_bytes_read != midi_chunk_length)
{
dt = get_var_len();
t += dt;
b = get_byte();
if(b & 0x80)
{
type = ((b>>4)&0x07);
if(type == 7)
{
if(b == 0xff)
{
meta_type = get_byte();
length = get_var_len();
if(meta_type != 0x2f)
{
meta_event = create_midi_meta_event(create_midi_message(b, meta_type, 0), t, length);
for(j = 0; j < meta_event->_data_size; j++) meta_event->_data[j] = get_byte();
add_midi_event(track, meta_event);
if(meta_type == 3)
{
get_track_name(track, meta_event->_data, length);
}
}
}
else if(b == 0xf0 || b == 0xf7)
{
length = get_var_len();
sysex_event = create_midi_sysex_event(create_midi_message(b, 0, 0), t, length+1);
for(j = 0; j < sysex_event->_data_size; j++) sysex_event->_data[j] = get_byte();
add_midi_event(track, sysex_event);
if(sysex_event->_data[length] != 0xf7)
{
	return NULL; /* sysex events terminate in 0xf7 */
}
}
else
{
return NULL; /* unknown message: cannot handle it */
}
running_status = 0;
}
else
{
if(bytes_per_msg[type] == 2)
{
b1 = get_byte();
add_midi_event(track, create_midi_event(create_midi_message(b, b1, 0), t));
}
else
{
b1 = get_byte();
b2 = get_byte();
add_midi_event(track, create_midi_event(create_midi_message(b, b1, b2), t));
}
running_status = b;
}
}
else
{
type = ((running_status >> 4) & 0x07);
if(bytes_per_msg[type] == 2)
{
add_midi_event(track, create_midi_event(create_midi_message(running_status, b, 0), t));
}
else
{
b2 = get_byte();
add_midi_event(track, create_midi_event(create_midi_message(running_status, b, b2), t));
}
}
}
song->_tracks[i] = track;
}
destroy_midi_chunk_type(chunk_type);
fclose(pfread);
return song;
}

int write_midi_file(const char* filename, const MIDISong* song)
{
	int type;
	int i, j, k;
unsigned long trkhd;
		long offset,endt;
		unsigned t0,t1;
int msglen;
const MIDIEvent* it = NULL;
static int bytespermsg[7] = {3, 3, 3, 3, 2, 3, 3};

init_fwrite_global_vars();
pfwrite = fopen(filename, "wb");
if(pfwrite == NULL) return 0;

_ntracks = song_tracks(song);
_format = (_ntracks > 1) ? 1 : 0;
_division = song_ticksperq(song);

write_header();
trkhd = MTrk;

for(i = 0; i < _ntracks; i++)
{
write_32bit(trkhd);
offset = ftell(pfwrite);
write_32bit(0);
_bytes_written = 0;
t0 = t1 = 0;
it = head_track(song->_tracks[i]);
while(it != NULL)
{
t1 = ticks_event(it);
type = ((it->_msg->_data[0] >> 4) & 0x07);
if(type == 7)
{
if(it->_msg->_data[0] == 0xff)
{
write_var_len(t1-t0);
write_char(it->_msg->_data[0]);
write_char(it->_msg->_data[1]);
write_var_len(data_size_event(it));
for(k = 0; k < data_size_event(it); k++)
{
write_char(it->_data[k]);
}
}
else if(it->_msg->_data[0] == 0xf0 || it->_msg->_data[0] == 0xf7)
{
	write_var_len(t1-t0);
	write_char(it->_msg->_data[0]);
	write_var_len(data_size_event(it)-1);
	for(k = 0; k < data_size_event(it); k++)
	{
	write_char(it->_data[k]);
	}
}
}
else
{
write_var_len(t1-t0);
msglen = bytespermsg[type];
for(j = 0; j < msglen; j++)
{
write_char(it->_msg->_data[j]);
}
}
t0 = t1;
it = next_event(it);
}
write_char(0);
write_char(0xff);
write_char(0x2f);
write_char(0);
endt = ftell(pfwrite);
fseek(pfwrite, offset, 0);
write_32bit(_bytes_written);
fseek(pfwrite, endt, 0);
}
fclose(pfwrite);
return 1;
}

/* END */
