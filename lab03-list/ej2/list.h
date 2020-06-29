#ifndef _LIST_H
#define _LIST_H

#include <stdbool.h>


/* node as a pointer to structs to guarantee encapsulation */
typedef int type_elem;
typedef struct Node *list; 

//CONSTRUCTORS

list empty(void);
/* 
    creates an empty list.
*/

list addl(list l, type_elem e);
/*
    adds the e element to the beginning of the list.
 */

list addr(list l, type_elem e);
/*
    adds the e element to the end of the list.
 */

//OPERATIONS

bool is_empty(list l);
/*
    returns true if l is empty.
 */ 

type_elem head(list l);
/*
    returns the first item in the list.
 */
 
list tail(list l);
/*
    deletes the first item from the list.
 */

int length(list l);
/*
    returns the number of items in the list.
*/

list concat(list l, list l1);
/*
    adds at the end of l all elements of l1 in the same order.
 */

type_elem index(list l, int n);
/*
    returns the n-umpteenth element of the list l.
 */

list take(list l, int n);
/*
    removes all elements of l located in the positions greater or equal to n.
 */

list drop(list l, int n);
/*
    removes all elements of l located in positions smaller than n.
 */

list copy_list(list  l); 
/*
    Makes a copy of list l. Allocates new memory.
*/
void print_list(list l);
/*
    print the entire list.
 */

//DESTROY
void destroy_list(list l);
/*
   Frees memory for l.
*/

#endif