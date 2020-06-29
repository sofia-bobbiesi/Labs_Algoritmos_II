#include<stdio.h>
#include<stdlib.h>

int main()
{

    int x = 20;
    int *p = NULL;
    
    p = &x; // p puntero que apunta a x
    *p = x*3; //*p reasigna un valor a la posicion que apunta
    
    printf("x = %d\n", x);

    return (EXIT_SUCCESS);
}
