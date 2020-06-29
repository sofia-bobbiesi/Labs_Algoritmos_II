#ifndef _SET_H_
#define _SET_H_

#include <stdbool.h>            /* Definition of bool      */
#include "type_elem.h"          /* Definition of type_elem */

typedef struct s_set *set;

/* CONSTRUCTORS */

set set_empty(void);

set set_add(set s, type_elem e);


/* OPERATIONS   */

unsigned int set_cardinal(set s);

bool set_is_empty(set s);

bool set_member(type_elem e, set s);

set set_elim(set s, type_elem e);

set set_union(set s, set s0);

set set_inters(set s, set s0);

set set_dif(set s, set s0);

type_elem set_get(set s);

set set_copy(set s);

set set_destroy(set s);

#endif
