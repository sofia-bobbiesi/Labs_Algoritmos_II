#include<stdio.h>
#include<stdlib.h>


int main()
{
    int x = 5;
    int y = -4;
    int *p = &x; 
    int *q = &y;
    int *r = p;
    
    // PART A: intercambie los valores referidos sin modificar los valores de p y q
    p = &y;
    q = &x;
    
    printf("El valor de *p=%d, *q=%d y *r=%d\n", *p, *q, *r);

    x = 5;
    y = -4;
    p = &x;
    q = &y;
    r = p;
    
    // PART B: intercambie los valores de los punteros
    r = p;
    p = q;
    q = r;
    
    printf("El valor de *p=%d, *q=%d y *r=%d\n", *p, *q, *r);
    
    return (EXIT_SUCCESS);
}
