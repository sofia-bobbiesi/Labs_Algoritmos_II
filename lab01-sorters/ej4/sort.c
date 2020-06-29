#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"

static unsigned int min_pos_from(int a[], unsigned int i, unsigned int length) {
    unsigned int min_pos = i;
    for (unsigned int j = i + 1; j < length; ++j) {
        if (!goes_before(a[min_pos],a[j])) {
            min_pos = j;
        }
    }
    return (min_pos);
}

void selection_sort(int a[], unsigned int length) {
    for (unsigned int i = 0u; i < length; ++i) {
        unsigned int min_pos = min_pos_from(a, i, length);
        swap(a, i, min_pos);
    }
}


static void insert(int a[], unsigned int i) {
    
    for (int j = i;(j>0 && goes_before(a[j],a[j-1])); j--)
    {
        swap(a,j-1,j);
    } 
}

void insertion_sort(int a[], unsigned int length) {
    for (unsigned int i = 1u; i < length; ++i) {
        insert(a, i);
    }
}


static unsigned int partition(int a[], unsigned int lft, unsigned int rgt) {
   unsigned int ppiv = lft, j = rgt, i = (lft + 1);

    while (i <= j)
    {
        if (goes_before(a[i],a[ppiv]))
        {
            i++;
        } else if (goes_before(a[ppiv],a[j]))
        {
            j--;
        } else 
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

       if(ppiv==0u)
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
