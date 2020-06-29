#ifndef _ARRAY_HELPERS_H
#define _ARRAY_HELPERS_H

#include <stdbool.h>

#define FST_YEAR 1980
#define LST_YEAR 2016
#define YEARS 37

typedef enum {january, february, march, april, may, june, july, august, september, october, november, december} t_month;
typedef enum {temp, temp_M, temp_m, press, moist, precip} t_phys_qtty;

#define MONTHS 12
#define PHYS_QTTYS 6

#define FST_DAY 1
#define LST_DAY 28
#define DAYS 28

void array_dump(int a[YEARS][MONTHS][DAYS][PHYS_QTTYS]);
/*
    Write the content of the array 'a' into stdout.
*/

void array_from_file(int a[YEARS][MONTHS][DAYS][PHYS_QTTYS], const char *filepath);
/*
    Each element is read from the file located at 'filepath'.
    The file must exist in disk and must have its contents in a sequence of
    lines, each with the following format:
    
    <year> <month> <day> <temperature> <high> <low> <pressure> <moisture> <precipitations>

    Those elements are copied into the multidimensional array 'a'.
    The dimensions of the array are given by the macro tclimate.
*/

#endif
