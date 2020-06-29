#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "helpers.h"
#include "sort.h"

static bool goes_before(player_t x, player_t y) {
    return (x.rank <= y.rank); 
}

bool array_is_sorted(player_t atp[], unsigned int length) {
    unsigned int i = 1;
    while (i < length && goes_before(atp[i - 1], atp[i])) {
        i++;
    }
    return (i == length);
}

void swap(player_t a[], unsigned int i, unsigned int j){
    player_t temp;
    
    temp = a[i];
    a[i] = a[j];
    a[j] = temp; 
}

// implementation of selection sort

static unsigned int min_pos_from(player_t a[], unsigned int i, unsigned int length) {
    unsigned int min_pos = i;
    for (unsigned int j = i + 1; j < length; ++j) {
        if (!goes_before(a[min_pos],a[j])) {
            min_pos = j;
        }
    }
    return (min_pos);
}

void selection_sort(player_t a[], unsigned int length) {
    for (unsigned int i = 0u; i < length; ++i) {
        unsigned int min_pos = min_pos_from(a, i, length);
        swap(a, i, min_pos);
    }
}

void sort(player_t a[], unsigned int length) {
    selection_sort(a,length);
}



