#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "array_helpers.h"


void array_dump(int a[YEARS][MONTHS][DAYS][PHYS_QTTYS]) {
    for (unsigned int year = 0u; year < YEARS; ++year) {
        for (t_month month = january; month <= december; ++month) {
            for (unsigned int day = 0u; day < DAYS; ++day) {
                fprintf(stdout, "%u %u %u", year + FST_YEAR, month + 1, day + 1);
                for (t_phys_qtty phqty = temp; phqty < PHYS_QTTYS; phqty++) {
                    fprintf(stdout, " %d", a[year][month][day][phqty]);
                }
                fprintf(stdout, "\n");
            }
        }
    }
}


void array_from_file(int a[YEARS][MONTHS][DAYS][PHYS_QTTYS], const char *filepath) {
    FILE *file = NULL;
    file = fopen(filepath, "r");
    if (file == NULL) {
	fprintf(stderr, "File does not exist.\n");
	exit(EXIT_FAILURE);
    }
    unsigned int k_year = 0u;
    unsigned int k_month = 0u;
    unsigned int k_day = 0u;
    int k_temp = 0; // media temp
    int k_temp_M = 0;
    int k_temp_m = 0;
    int k_press = 0;
    int k_moist = 0;
    int k_precip = 0;
    while (!feof(file)) {
        int res = fscanf(file, " %u %u %u %d %d %d %d %d %d ", &k_year, &k_month, &k_day, &k_temp, &k_temp_M, &k_temp_m, &k_press, &k_moist, &k_precip);
	if (res != 9) {
            fprintf(stderr, "Invalid array.\n");
            exit(EXIT_FAILURE);
        }
        a[k_year - FST_YEAR][k_month - 1][k_day - 1][temp] = k_temp;
        a[k_year - FST_YEAR][k_month - 1][k_day - 1][temp_M] = k_temp_M;
        a[k_year - FST_YEAR][k_month - 1][k_day - 1][temp_m] = k_temp_m;
        a[k_year - FST_YEAR][k_month - 1][k_day - 1][press] = k_press;
        a[k_year - FST_YEAR][k_month - 1][k_day - 1][moist] = k_moist;
        a[k_year - FST_YEAR][k_month - 1][k_day - 1][precip] = k_precip;
    
    }
    fclose(file);
}
