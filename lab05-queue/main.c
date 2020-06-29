/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Then, this project's includes, alphabetically ordered */
#include "queue.h"

#define ENQUEUE 'e'
#define DEQUEUE 'd'
#define SHOW    'h'
#define SIZE    'z'
#define FIRST   'f'
#define QUIT    'q'

#define RESULT_PREFIX "\t-> "

char print_menu(void) {
    char option;
    printf("\nChoose what you want to do. Options are:\n"
           "\n"
           "\t**************************************************************\n"
           "\t* z: Size of the queue                                       *\n"
           "\t* e: Queue the element element to the queue q                *\n"
           "\t* d: Dequeue the first element of the queue                  *\n"
           "\t* h: Show the status of the queue                            *\n"
           "\t* f: Returns the first element of the queue                  *\n"
           "\t* q: Quit                                                    *\n"
           "\t**************************************************************\n"
           "\nPlease enter your choice: ");

    scanf(" %c",&option);
    while ((getchar()) != '\n');
    return option;
}

void on_enqueue(queue q){
    elem_t elem = 0;  
    printf("Please enter an element on the queue: ");
    scanf("%d", &elem);
    q = queue_enqueue(q, elem);
    printf("\tYour element was successfully queued.\n");
}

void on_dequeue(queue q){
    unsigned int l_tmp = queue_size(q);
    q = queue_dequeue(q);
    if ((l_tmp-1) == queue_size(q)){
    printf("\tYour element was successfully queued.\n");
    }
}

void on_show(queue q){
    printf("The queue is: \n");
    queue_print(q);
    printf("\nThe queue is empty? %s", queue_is_empty(q) ? "Yes" : "No");
}
void on_size(queue current) {
    printf("The size of the queue is %lu\n", queue_size(current));
}

void on_first(queue q){
    printf("The first elemnt is: %d",queue_first(q));
}

int main(void) {
    char option = '\0';
    queue current = queue_empty();
    /* print a simple menu and do the requested operations */
    do {
        option = print_menu();
        switch (option) {
            case ENQUEUE:
            on_enqueue(current);
                break;
            case DEQUEUE:
            on_dequeue(current);
                break;
            case SHOW:
            on_show(current);
                break;
            case SIZE:
            on_size(current);
                break;
            case FIRST:
            on_first(current);
                break;
            case QUIT:
                current = queue_free(current);
                printf("\033[1;36m"); 
                printf("Thanks for testing. Bye ♥\n");
                printf("\033[0m");
                printf(RESULT_PREFIX "Exiting.\n");
                return (EXIT_SUCCESS);
            default:
                printf("\n\"%c\" is invalid. Please choose a valid "
                       "option.\n\n", option);
        }
    } while (option != QUIT);
    return (EXIT_SUCCESS);
}
