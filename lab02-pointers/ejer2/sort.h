#ifndef _SORT_H
#define _SORT_H

#include <stdbool.h>

bool array_is_sorted(player_t atp[], unsigned int length);
/*
   Checks if the array 'a' is in ascending order according
   to the goes_before function
*/

void sort(player_t a[], unsigned int length);
/*
    Sort the array 'a' using any sorting algorithm. The resulting sort
    will be ascending according to the goes_before funtion.

    The array 'a' must have exactly 'length' elements.
*/


#endif
