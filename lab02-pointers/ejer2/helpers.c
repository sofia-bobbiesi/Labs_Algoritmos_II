#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"

void array_copy(player_t copy[], player_t array[], unsigned int length) {
    for (unsigned int i = 0; i < length; i++) {
        copy[i] = array[i];
    }
}

static unsigned int array_value_count(player_t a[], unsigned int length, player_t value) {
    unsigned int count = 0;
    for (unsigned int i = 0; i < length; i++) {
	if (a[i].name == value.name) {
	    count++;
	}
    }
    return (count);
}

bool array_is_permutation_of(player_t a[], player_t b[], unsigned int length) {
    unsigned int i = 0;
    bool result = true;
    while (i < length && result) {
	unsigned int a_count = array_value_count(a, length, a[i]);
	unsigned int b_count = array_value_count(b, length, a[i]);
	result = (a_count == b_count);
	i++;
    }
    return (result);
}

static void process_name(FILE *file, char name[]) {
    unsigned int i = 0;
    char c;
    while ((c = fgetc(file)) != ' ') {
       name[i] = c;
       i++;
    }
    name[i] = '\0';
}

static void process_country(FILE *file, char country[]) {
    country[0] = fgetc(file);
    country[1] = fgetc(file);
    country[2] = fgetc(file);
    country[3] = '\0';
}

static unsigned int process_unsigned(FILE *file) {
    unsigned int value = 0;
    int res = fscanf(file, " %u ", &value);
    if (res != 1) {
        fprintf(stderr, "Invalid array.\n");
        exit(EXIT_FAILURE);
    }
    return (value);
}

void atp_dump(player_t atp[], unsigned int length) {
    for (unsigned int i = 0; i < length; i++) {
        fprintf(stdout,"%s ", atp[i].name);
        fprintf(stdout,"%s ", atp[i].country);
        fprintf(stdout,"%u %u %u %u\n", atp[i].rank, atp[i].age, atp[i].points, atp[i].tournaments);
    }
}

static unsigned int process_FILE(FILE *file, player_t atp[]) {
    unsigned int i = 0;
    while (!feof(file) != '\0') {
        process_name(file, atp[i].name);
        process_country(file, atp[i].country);
        atp[i].rank = process_unsigned(file);
        atp[i].age = process_unsigned(file);
        atp[i].points = process_unsigned(file);
        atp[i].tournaments = process_unsigned(file);
        i++;
    }
    return (i);
}

unsigned int process_file(const char *filepath, player_t atp[]) {
    unsigned int size = 0;
    FILE *file = NULL;
    file = fopen(filepath, "r");
    if (file == NULL) {
	fprintf(stderr, "File does not exist.\n");
	exit(EXIT_FAILURE);
    }
    size = process_FILE(file, atp);
    fclose(file);
    return (size);
}
