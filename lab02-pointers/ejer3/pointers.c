#include <stdio.h>
#include <stdlib.h>

typedef struct _person {
    int age;
    char name_initial;
} person_t;


int main(void) {

    int x = 1;
    person_t m = {90, 'M'};
    int a[] = {0, 1, 2, 3};

    int *p = NULL;
    char *q = NULL;

    p = &x;
    *p += 8;

    p = &m.age;
    *p += 10;

    p = &a[1];
    *p += 41;

    q = &m.name_initial;
    *q -= 7; //the ASCII code of H is 77 and that of F 70

    printf("x = %d\n", x);
    printf("m = (%d, %c)\n", m.age, m.name_initial);
    printf("a[1] = %d\n", a[1]);

    return (EXIT_SUCCESS);
}
