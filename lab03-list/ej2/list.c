#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "list.h"


struct Node
{
    type_elem elem; //Value that the structure will have in each element, in this case is an integer number
    struct Node* next; //Pointer to the next node
};


//CONSTRUCTORS

list empty(void){ 
    list l = NULL;

    return l;
}

list addl(list l, type_elem e){
    list l_temp = (list)malloc(sizeof(struct Node));
    l_temp -> elem = e;
    l_temp -> next = l;
    l = l_temp;

    return l;
}

list addr(list l, type_elem e){ 
    list l_temp = (list)malloc(sizeof(struct Node)),l_aux = l;
    l_temp ->elem = e;
    l_temp ->next = NULL;

    if (l == NULL){
        l = l_temp;
    }
    else{
        while (l_aux ->next){ //equivalent to saying (l_aux->next != NULL)
        l_aux = l_aux->next;
        }
    l_aux -> next = l_temp;
    }

    return l;
} 

//OPERATIONS

bool is_empty(list l){ 
    return l == NULL;
}

type_elem head(list l){
    assert(!is_empty(l));
    return l -> elem;
}
 
list tail(list l){ 
   assert(!is_empty(l));
    list l_temp = l;
    l = l -> next;
    free(l_temp);

    return l;
}

int length(list l){
    int length = 0;
    list l_temp = l;

    while (l_temp){ 
        length++;
        l_temp = l_temp->next;
    }
    return length; 
}

list concat(list l1, list l2){ 
    /*Do not use concat(l,l), since they both have the same memory space you 
    WILL create a circular list, do concat(l,copy_list(l)) instead as that 
    will have different memory spaces*/
    if (l1 == NULL){
        return l2;
    }
    else if (l2 == NULL){
        return l1;
    }
    /*if both lists are not null, they concatenate */
    list l_temp = l1;
    while (l_temp->next){ 
        l_temp = l_temp->next;
    } 
     /*now we can add a new list */
    l_temp -> next = l2;
    
    return l1;
}
 
type_elem index(list l, int n){
    assert(length(l)>n);
    list l_temp = l;
    for (int i = 0; i < n; i++){
        l_temp = l_temp -> next;
    }
    return l_temp -> elem;
}

list take(list l, int n){
    int i=(length(l)-n);
    for (int j = 0; j < i; j++) {
        list l_temp = l;
        while (l_temp->next->next!=NULL)
        {
            l_temp=l_temp->next;
        }
        free(l_temp->next);
        l_temp->next=NULL;
    }
    return l;
} 

list drop(list l, int n){ 
  for (int i = 1; i < n; i++){
        l = tail(l);
    }
    return l;
}

list copy_list(list l){
    list l_copy = empty(), l_temp=l;
    while (l_temp){   
        l_copy = addr(l_copy,l_temp->elem);
        l_temp = l_temp->next;
    }
    return l_copy;
}

void print_list(list l){ 
    while (l) { 
        printf("%d ",l->elem); 
        l = l->next; 
    } 
} 

//DESTROY

void destroy_list(list l){
    list l_temp = l;
    while(l){
        l = l -> next;
        free(l_temp);
        l_temp = l;
    }
} 