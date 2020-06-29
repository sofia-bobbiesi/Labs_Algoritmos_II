#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include "counter.h"

struct _counter {
    unsigned int count;
};

counter init(void) {

    counter c = (counter)malloc(sizeof(struct _counter));
    assert(c != NULL);
    c -> count = 0;
    
    return c;
}

void inc(counter c) {
    c -> count++; 
}

bool is_init(counter c) {
    return c -> count == 0;
}

void dec(counter c) {

    assert(!(is_init(c)));
        c -> count--;
}

counter copy_counter(counter c) { //NI SIQUIERA LA USA, EL PROBLEMA NO ES ACA
    counter copy = NULL;
    copy->count=c->count;

    return copy;
}

void destroy_counter(counter c) {
    free(c);
}
