#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"


static unsigned int partition(int a[], unsigned int lft, unsigned int rgt) {
    /* Permutes elements of a[izq..der] and returns pivot such that:
     - izq <= pivot <= der
     - elements in a[izq,pivot) all 'go_before' (according to function goes_before) a[pivot]
     - a[pivot] 'goes_before' all the elements in a(pivot,der] */
   unsigned int ppiv = lft;
   unsigned int j = rgt;
   unsigned int i = (lft + 1);
    while (i <= j)
    {
        if (goes_before(a[i],a[ppiv]))
        {
            i++;
        } else if (goes_before(a[ppiv],a[j]))
        {
            j--;
        } else  //  if (goes_before(a[ppiv],a[i]) && goes_before(a[j],a[ppiv]))
        {
            swap(a,i,j);
            i++;
            j--;
        }
    }
    swap(a,ppiv,j);
    ppiv=j;

    return(ppiv); 


}
    



 
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
    quick_sort_rec(a, 0, (length == 0) ? 0 : length - 1);
}

