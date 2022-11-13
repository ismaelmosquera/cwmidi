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
#include "midi_player.h"

void show_menu();
void list_midi_out_devs(char**, int);

int main()
{
	char s[64];
	int option;
int has_midi = 0;
int dev_id = 0;
int ndevs = 0;
char** devlst = get_midi_out_devs(&ndevs);
if(ndevs < 1)
{
printf("No MIDI out device found in your system.\n");
return 1;
}

	show_menu();
	do
	{
		printf("\noption: ");
		scanf("%d", &option);
		if(option == 0) option = 7;
		switch(option)
		{
			case 1:
			show_menu();
			break;
			case 2:
list_midi_out_devs(devlst, ndevs);
printf("enter id: ");
scanf("%d", &dev_id);
if(dev_id >= 0 && dev_id < ndevs)
{
	set_midi_out_port(dev_id);
	printf("\nmidi out port id set to %d\n", dev_id);
}
else
{
	printf("\nMIDI port must be in the range 0 .. %d\n", ndevs-1);
}
			break;
			case 3:
			stop_midi();
			printf("filename: ");
			scanf("%s", s);
			if(load_midi(s))
			{
				has_midi = 1;
				printf("\nmidi file loaded successfully.\n");
			}
			else
			{
				printf("\ncannot load midi file.\n");
			}
			break;
			case 4:
			if(has_midi)
			{
			if(play_midi() != 0)
			{
				printf("cannot play midi, or the player is already playing.\n");
			}
		}
		else
		{
			printf("Sorry, no midi file has been loaded yet.\n");
		}
			break;
			case 5:
			stop_midi();
			break;
			case 6:
			stop_midi();
			option = 0;
			break;
			default:
			printf("unknown option.\n");
		}
	}while(option != 0);

	printf("\nbye\n");

return 0;
}

void show_menu()
{
printf("1 - show menu\n");
printf("2 - select midi out device\n");
printf("3 - load midi\n");
printf("4 - play midi\n");
printf("5 - stop midi\n");
printf("6 - exit\n");
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
