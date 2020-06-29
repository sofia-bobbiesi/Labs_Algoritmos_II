#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"


static void quick_sort_rec(int a[], unsigned int lft, unsigned int rgt) {

   int ppiv=0;
   
   if(lft < rgt)
   {
       
       ppiv=partition(a,lft,rgt);

       if(ppiv==0) // 0u es el literal de los sin signo
       {
        quick_sort_rec(a,lft,ppiv);
       } else {
        quick_sort_rec(a,lft,ppiv-1);
       }
       quick_sort_rec(a,ppiv+1,rgt);

   }

}

void quick_sort(int a[], unsigned int length) {
    quick_sort_rec(a, 0u, (length == 0u) ? 0u : length - 1u);
}

