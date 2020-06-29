#ifndef _LIST_H_
#define _LIST_H_

#include <stdbool.h>   /* Definition of bool      */
#include "type_elem.h" /* Definition of type_elem */

/* Definition of datatype list */
typedef struct node_t * list;

/* CONTRUCTORS */

list list_empty(void);
/*
 * DESC: Creates a new empty list
 * USAGE: l = list_empty();
 * POS  : {list_is_empty(l)}
 */

list list_addl(list l, type_elem e);
/*
 * DESC: Adds element 'e' to the start of list 'l'
 * PRE  : {list_length(l) == N}
 * USAGE: l = list_addl(l, e);
 * POS  : {list_length(l) == N + 1 /\ e == list_head(l)}
 */


/* OPERATIONS */

list list_addr(list l, type_elem e);
/*
 * DESC: Adds element 'e' to the end of list 'l'
 * PRE  : {list_length(l) == N}
 * USAGE: l = list_addl(l, e);
 * POS  : {list_length(l) == N + 1 /\ e == list_index(l, list_length(l) - 1)}
 */


unsigned int list_length(list l);
/*
 * DESC: Returns the size of list 'l'
 * USAGE: n = list_length(l);
 */

bool list_is_empty(list l);
/*
 * DESC: Indicates if there are no elements in list 'l'
 * USAGE: is_empty = list_is_empty(l);
 * POS  : {is_empty == (list_length(l) == 0)}
 */

type_elem list_head(list l);
/*
 * DESC: Returns first element of 'l'
 * PRE  : {!list_is_empty(l)}
 * USAGE: e = list_head(l);
 * POS  : {e == list_index(l, 0)}
 *
 */

list list_tail(list l);
/*
 * DESC: Discards first element of list 'l'
 * PRE  : {!list_is_empty(l) /\ list_length(l) == N}
 * USAGE: l = list_tail(l);
 * POS  : {list_length(l) == N - 1}
 *
 */

list list_concat(list l, list l2);
/*
 * DESC: Concatenates list l with l2. The elements of 'l2' are copied into 'l'.
 * PRE  : {list_length(l) == N /\ list_length(l2) == M}
 * USAGE: l = list_concat(l, l2);
 * POS  : {list_length(l) == N + M}
 *
 */

type_elem list_index(list l, unsigned int n);
/*
 * DESC: Gets the n-nth element of list 'l'
 * PRE   : {n < list_length(l)}
 * USAGE : e = list_index(l, n)
 *
 */


list list_take(list l, unsigned int n);
/*
 * DESC: Keeps the n first elements of list 'l' and destroy the rest of them.
 * PRE  : {list_length(l) == N}
 * USAGE: l = list_take(l, n);
 * POS  : {list_length(l) == min(n, N)}
 */

list list_drop(list l, unsigned int n);
/*
 * DESC: Drops (and destroys) the first n elements of list 'l'.
 * PRE  : {list_length(l) == N}
 * USAGE: l = list_drop(l, n);
 * POS  : {(n <= N /\ list_length(l) == N - n) \/ (n > N /\ list_is_empty(l))}
 */


list list_add_at(list l, unsigned int n, type_elem e);
/*
 * DESC: Insert element 'e' to the n-nth position of list 'l'
 * PRE  : {n <= list_length(l) /\ list_length(l) == N}
 * USAGE: l = list_drop(l, n);
 * POS  : {list_length(l) == N + 1 /\ e == list_index(l, n)}
 */

list list_elim_at(list l, unsigned int n);
/*
 * DESC: Deletes the n-nth element of list 'l'
 * PRE  : {n < list_length(l) /\ list_length(l) == N}
 * USAGE: l = list_drop(l, n);
 * POS  : {list_length(l) == N - 1}
 */

list list_copy(list l);
/*
 * DESC: Returns a copy of the list 'l' with new memory.
 * USAGE: l2 = list_copy(l);
 * POS  : {list_length(l) == list_length(l2) /\ (l != l2 \/ is_empty(l)}
 */


list list_destroy(list l);
/*
 * DESC: Destroy list 'l' by freeing all the allocated resources.
 * USAGE: l = list_destroy(l);
 * POS  : {l == NULL}
 */
#endif
