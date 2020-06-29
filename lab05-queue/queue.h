#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdio.h>
#include <stdbool.h>

typedef int elem_t;
typedef struct node_t *node;
typedef struct queue_t *queue;

/* CONSTRUCTORS */

queue queue_empty(void);
/* Returns a new queue created, empty
 *
 * PRE: 
 * 
 *  q = queue_empty();
 * 
 * POS: 
 * 
 */

queue queue_enqueue(queue q, elem_t elem);
/* Queue the element elem to the queue q
 *
 * PRE:
 * 
 *  q = queue_enqueu(q, elem);
 * 
 * POS: 
 * 
 */

/* OPERATIONES */

size_t queue_size(queue q);
/*  Returns the size of the queue
 * 
 * PRE:
 *  
 *  n = queue_size(q);
 * 
 * POS:
 * 
 */ 

bool queue_is_empty(queue q);
/*  Returns the size of the queue
 * 
 * PRE:
 * 
 *  is_empty = queue_is_empty(q);
 * 
 * POS:
 * 
 */ 

elem_t queue_first(queue q);
/*  Returns the first element in the queue (the first element added).
 *  Doesn't modify the q queue, only returns a COPY of the first element.
 * 
 * PRE:
 * 
 *  elem = queue_first(q);
 * 
 * POS:
 * 
 */

queue queue_dequeue(queue q);
/*  Dequeue the first element of the queue.
 * 
 * PRE:
 * 
 *  q = queue_dequeue(q);
 * 
 * POS:
 * 
 */ 


void queue_print(queue q);
/* Print all the elements in queue.
 * 
 * PRE:
 * 
 *  queue_print(q);
 * 
 * POS:
 * 
 */

queue queue_free(queue q);
/* Frees the resources ordered to the system by queue q.
 * 
 * PRE:
 * 
 *  q = queue_free(q)
 * 
 * POS:
 * 
 */

#endif