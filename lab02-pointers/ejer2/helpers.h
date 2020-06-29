#ifndef _HELPERS_H
#define _HELPERS_H

#include <stdbool.h>

typedef struct _player_t {
    char name[100];
    char country[4];
    unsigned int rank;
    unsigned int age;
    unsigned int points;
    unsigned int tournaments;
} player_t;

bool array_is_permutation_of(player_t a[], player_t other[], unsigned int length);
/*
    Return whether the array 'other' is a permutation of the array 'a'.

    The arrays 'a' and 'other' must have both the same 'length'.
*/

void array_copy(player_t dst[], player_t src[], unsigned int length);
/* 
    Copy the array 'src' into the array 'dst' 
*/

unsigned int process_file(const char *filepath, player_t atp[]);
/*
    Loads the contents of the file into the array of players.
*/

void atp_dump(player_t atp[], unsigned int length);
/*
    Prints the contents of the array of players to standard output.
*/

#endif
