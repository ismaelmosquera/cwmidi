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

#ifndef ___RAND_H___
#define ___RAND_H___

#ifdef __cplusplus
extern "C"{
	#endif

/*
* Inits the random process
*/
void randomize();

/*
* Gets a random number between min and max where min and max are included
*/
int random(int min,int max);

/*
* Takes an array as input and gets another array as output
* The output array is build from the input array
*
* in[] => the input array
* size_in => size of the input array
* out[] => the output array
* size_out => the size of the output array
* allow_dup => flag to ask for allow duplicates
* allow_dup = 0 => do not allow duplicates
* allow_dup = 1 => allow duplicates
*
* The size of the output array must be less or equal to the size of the input array
*
* If you don't want duplicates,
* an input array without duplicates is required
*/
void rand_array(int in[],int size_in,int out[],int size_out,int allow_dup);

/*
* Fills the array passed as parameter with random numbers
* in[] => array to be filled
* size => size of the input array
* min..max => range for random numbers where min and max are included
*/
void fill_rand(int in[], int size, int min, int max);

#ifdef __cplusplus
}
	#endif

#endif
