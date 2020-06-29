#define _WEATHER_H
#include <stdio.h>
#include <stdlib.h>
#include "array_helpers.h"

int min_temp_min(int a[YEARS][MONTHS][DAYS][PHYS_QTTYS]);
/*
    returns the minimun value of the minimun temperature of all years
 */

void max_temp_years(int a[YEARS][MONTHS][DAYS][PHYS_QTTYS]);
/*
    returns the value of the maximum temperature in each year
 */

void max_precip_months( int a[YEARS][MONTHS][DAYS][PHYS_QTTYS]);
/*
    returns the month in which the maximum precipitation was recorded of every year
 */
