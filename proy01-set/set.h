#ifndef _SET_H_
#define _SET_H_

#include <stdbool.h>   /* Definition of bool      */
#include "type_elem.h" /* Definition of type_elem */

typedef struct s_set * set;

/* CONSTRUCTORS */

set set_empty(void);
/*
 * DESC : Creates a new empty set
 * USAGE: s = set_empty();
 * POS  : {set_is_empty(s)}
*/

set set_add(set s, type_elem e);
/*
 * DESC : Adds element e to set s, respecting the order
 * PRE  : {set_cardinal(s) == N} 
 * USAGE: s = set_add(s,e);
 * POS  : {set_cardinal(s) == N + 1 /\ e == set_member(s)}
 */

/* OPERATIONS   */

unsigned int set_cardinal(set s);
/*
 * DESC : Returns the number of items in s 
 * USAGE: n = set_cardinal(s);
 */

bool set_is_empty(set s);
/*
 * DESC : Returns True if s is empty
 * USAGE: is_empty = set_is_empty(s);
 * POS  : {is_empty == (set_cardinal(s)) == 0)}
 */

bool set_member(type_elem e, set s);
/*
 * DESC : Returns True if element e belongs to set s
 * PRE  : {not set_is_empty(s)}
 * USAGE: is_member = set_member(e,s)
 * POS  : {is_member \/ not is_member}
 */

set set_elim(set s, type_elem e);
/*
 * DESC : Removes the element e from the set s, if it exist
 * PRE  : {set_cardinal(s) == N /\ set_member(e,s)}
 * USAGE: s = set_elim(s,e)
 * POS  : {set_cardinal(s) == N-1 /\ not set_member(e,s)}
 */

set set_union(set s, set s0);
/*
 * DESC : Adds to s all elements of s0
 * PRE  : {set_cardinal(s) == N /\ set_cardinal(s0) == M}
 * USAGE: s_u = set_union(s,s0)
 * POS  : {set_cardinal(s_u) ≤ N + M}
 */

set set_inters(set s, set s0);
/*
 * DESC : Deletes s from all elements that do NOT belong to s0
 * PRE  : {set_member(e,s) /\ set_member(e,s0)}
 * USAGE: s_i = set_inters(s,s0)
 * POS  : {set_member(e,s_i)}
 */

set set_dif(set s, set s0);
/*
 * DESC : Removes of s all elements belonging to s0
 * PRE  : {set_cardinal(s) == N /\ set_cardinal(s0) == M}
 * USAGE: s_d = set_dif(s)
 * POS  : {set_cardinal(s_d) ≥ N - M} 
 */

type_elem set_get(set s);
/*
 * DESC : Get the first element of the set s
 * PRE  : not set_is_empty(s)
 * USAGE: element = set_get(s)
 * POS  : {element != NULL}
 */

set set_copy(set s);
/*
 * DESC : Copy the set s
 * USAGE: s0 = set_copy(s)
 * POS  : {set_cardinal(s) == set_cardinal(s0) /\ (s != s0 \/ set_is_empty(s)}
 */

set set_destroy(set s);
/*
 * DESC : Frees memory in case it has been requested.
 * USAGE: s = set_destroy(s);
 * POS  : {s = NULL}
 */

#endif
