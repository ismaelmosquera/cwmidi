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

#include <stdlib.h>
#include <time.h>
#include "rand.h"

/* implementation */

void randomize()
{
/* Use the system's time as a seed */
srand((unsigned)time(NULL));
}

int random(int min,int max)
{
int result, range;
if(min >= max) return 0;
 range = (max - min) + 1;
return (rand() % range) + min;
}

void rand_array(int in[],int size_in, int out[], int size_out, int allow_dup)
{
int i, val, flag;
int aux[size_in];
if(!allow_dup && size_out > size_in) return;
if(!allow_dup) for(i = 0; i < size_in; i++) aux[i] = 0;
flag = 1;
i = 0;
while(i < size_out)
{
val = random(0, size_in - 1);
if(!allow_dup)
{
if(!aux[val])
{
aux[val] = 1;
flag = 1;
}
else
{
flag = 0;
}
}
if(flag) out[i++] = in[val];
}
}

void fill_rand(int in[], int size, int min, int max)
{
int i;
if(min >= max) return;
for(i = 0; i < size; i++) in[i] = random(min, max);
}

/* END */
