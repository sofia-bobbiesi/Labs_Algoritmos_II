#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "weather.h"

int min_temp_min(int a[YEARS][MONTHS][DAYS][PHYS_QTTYS]){
    int min = a[0u][january][0u][temp_m];

    for (unsigned int year = 0u; year < YEARS; ++year) {
        for (t_month month = january; month <= december; ++month) {
            for (unsigned int day = 0u; day < DAYS; ++day) {
                if(a[year][month][day][temp_m] < min){ 
                    min = a[year][month][day][temp_m];
                }
            }
        }
    }

    return min;
}

void max_temp_years( int a[YEARS][MONTHS][DAYS][PHYS_QTTYS]) {

    for (unsigned int year = 0u; year < YEARS; ++year) {

        int max_tmp = a[0u][january][0u][temp_M];

        for (t_month month = january; month <= december; ++month) {

            for (unsigned int day = 0u; day < DAYS; ++day) {

                if(a[year][month][day][temp_M] > max_tmp){ 

                    max_tmp = a[year][month][day][temp_M];
                }
            }
        } 
       printf("\nYear %u, max temp %d\n",year+1980u,max_tmp);
    }
    printf("\n\n");
}

void max_precip_months( int a[YEARS][MONTHS][DAYS][PHYS_QTTYS]) {
    
    for (unsigned int year = 0u; year < YEARS; ++year) {
        
        int m_month = january;
        int max_precip = 0;

        for (t_month month = january; month <= december; ++month) {
            
            int sum_precip = 0;

            for (unsigned int day = 0u; day < DAYS; ++day) {

                sum_precip += a[year][month][day][precip];
            } 

            if (sum_precip > max_precip){
                max_precip = sum_precip;
                m_month = month;
            }
        }  
      printf("\nYear %u, month of max precip %d\n",year+1980u,m_month+1); //start counting at 0
    }
    printf("\n\n");
}
