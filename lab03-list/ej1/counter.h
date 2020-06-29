#ifndef _COUNTER_H
#define _COUNTER_H

#include <stdbool.h>

/* counter as a pointer to structs to guarantee encapsulation */
typedef struct _counter * counter;


/* Constructors */
counter init(void);
/*
    Create a new counter with initial value. Allocates new memory.
    Being c the returned counter, is_init(c) should be true.
*/

void inc(counter c);
/*
    Increments the counter c.
*/


/* Operations */
bool is_init(counter c);
/*
    Return whether the counter c has the initial value.
*/

void dec(counter c);
/*
    Decrements the counter c.
    PRECONDITION: !is_init(c)
*/

counter copy_counter(counter c);
/*
    Makes a copy of counter c. Allocates new memory.
*/

void destroy_counter(counter c);
/*
   Frees memory for c.
*/

#endif
