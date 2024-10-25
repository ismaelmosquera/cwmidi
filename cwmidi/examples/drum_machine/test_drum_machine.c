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
#include <stdlib.h>
#include "midi_out_dev_list.h"
#include "drum_machine.h"


void show_menu();

int main()
{
	char opt[7];
	int option;
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
		scanf("%s", opt);
		option = atoi(opt);
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
	set_midi_out_id(dev_id);
	printf("\nmidi out port id set to %d\n", dev_id);
}
else
{
	printf("\nMIDI port must be in the range 0 .. %d\n", ndevs-1);
}
			break;
			case 3:
			if(start_drum_machine() != 0)
			{
				printf("cannot start drum machine, or the player is already playing.\n");
			}
			break;
			case 4:
			stop_drum_machine();
			break;
			case 5:
			stop_drum_machine();
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
printf("3 - start drum machine\n");
printf("4 - stop drum machine\n");
printf("5 - exit\n");
}


/* END */
