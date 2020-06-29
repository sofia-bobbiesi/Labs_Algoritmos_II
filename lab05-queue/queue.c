#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"

struct node_t{
    elem_t data;
    node next;
};

struct queue_t{
    node front;
    node rear;
    size_t length;
};

queue queue_empty(void){
    queue q = (queue)malloc(sizeof(struct queue_t));
    q -> length = 0;
    q -> front = NULL;
    q -> rear = NULL; 
    return q;
}

queue queue_enqueue(queue q, elem_t elem){
    node q_tmp = (node)malloc(sizeof(struct node_t));
    q_tmp->data = elem;
    q_tmp->next = NULL;

    if(q->front == NULL){
        q->front = q_tmp;
        q->rear = q_tmp;
    }
    else{
        q->rear->next = q_tmp;
        q->rear = q_tmp; //reasignar cual es el ultimo ahora
    }
    q->length++;
    return q;
}

/* OPERATIONES */

size_t queue_size(queue q){
    return q->length; //???
}

bool queue_is_empty(queue q){
    return (q->front == NULL && q->rear == NULL);
}

elem_t queue_first(queue q){
    return q->front->data;
}

queue queue_dequeue(queue q){
    if(q->front != NULL){
    node q_temp = q->front;
    q->front = q->front->next;
    q->length--;
    free(q_temp);
    }
    return q;
}

void queue_print(queue q){
    if (q->front){
        node q_temp = q->front;
        printf("{%d",q_temp->data);
        q_temp = q_temp->next;
        while(q_temp != NULL){
            printf(", ");
            printf("%d",q_temp->data);
            q_temp = q_temp->next;
         }
    printf("}");
    free(q_temp);
    }
    else{
        printf("{}");
    } 
}

queue queue_free(queue q){
    while(q->front != NULL){
        q = queue_dequeue(q);
    }
    free(q);
    return NULL;
}