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

#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include <string.h>
#include "midi_out_dev_list.h"


/* implementation */

char** get_midi_out_devs(int* numdevs)
{
	int i;
int ndevs = 0;
char** dev_lst;
MIDIOUTCAPS     moc;
ndevs = midiOutGetNumDevs();
dev_lst = (char**)malloc(ndevs * sizeof(char*));
for(i = 0; i < ndevs; i++)
{
	if(!midiOutGetDevCaps(i, &moc, sizeof(MIDIOUTCAPS)))
	{
		dev_lst[i] = (char*)malloc((strlen(moc.szPname)+1) * sizeof(char));
		strcpy(dev_lst[i], moc.szPname);
	}
}
*numdevs = ndevs;
return dev_lst;
}

void list_midi_out_devs(char** dev_list, int ndevs)
{
int i;
printf("\nAvailable midi out devices in your system:\n");
for(i = 0; i < ndevs; i++)
{
	(i == 0) ? printf("Dev ID: %d - %s ( default )\n", i, dev_list[i]) : printf("Dev ID: %d - %s\n", i, dev_list[i]);
}
}


/* END */
