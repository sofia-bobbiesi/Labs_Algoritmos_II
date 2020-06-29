#include <assert.h>
#include "list.h"
#include "set.h"
#include <stdbool.h> /* Definition of bool */
#include <stdlib.h>
#include "type_elem.h" /* Definition of type_elem */


struct s_set{
    list sorted_list;
};

/* CONSTRUCTORS */

set set_empty(void){
    set s = (set)malloc(sizeof(struct s_set));
    s -> sorted_list = list_empty();
    return s;
}


set set_add(set s, type_elem e){
    set saux = set_copy(s);
    bool is_member = false;
    int n=0;

    /* find the place where the item goes */
    while ((!list_is_empty(saux->sorted_list))&&(!is_member)){   
        type_elem d = list_head(saux->sorted_list);
        if (d == e){
            is_member = true;
        }
        else if (d < e){
            n++;
        }
        saux->sorted_list = list_tail(saux->sorted_list);
    }
    if(!is_member){
        s->sorted_list = list_add_at(s->sorted_list,n,e);
    }
    saux = set_destroy(saux);
    return s;
}

unsigned int set_cardinal(set s){
    unsigned int n = list_length(s->sorted_list);
    return n;
}

bool set_is_empty(set s){
    return list_is_empty(s->sorted_list);
}

bool set_member(type_elem e, set s){
    type_elem d;
    set saux = set_copy(s);
    bool is_member = false;

    while (!set_is_empty(saux) && !is_member){
        d = list_head(saux->sorted_list);
        if (e == d){
            is_member = true;
        }
        saux ->sorted_list = list_tail(saux->sorted_list);
    }
    saux = set_destroy(saux);
    return is_member;
}

set set_elim(set s, type_elem e){
   if(set_member(e,s)){
    type_elem d;

    for (unsigned int i = 0; i <list_length(s->sorted_list); i++){
        d = list_index(s->sorted_list,i);
        if (e == d){
            s->sorted_list = list_elim_at(s->sorted_list,i);
        }
    }
   }
    return s;
}

set set_union(set s, set s0){
    set saux = set_copy(s0);
    type_elem d;

    while (!set_is_empty(saux)){
        d = list_head(saux->sorted_list);
        s = set_add(s,d);
        saux->sorted_list = list_tail(saux->sorted_list);
    }
    saux = set_destroy(saux);
    return s;
}

set set_inters(set s, set s0){
    set saux = set_copy(s);
    type_elem d;
    while (!set_is_empty(saux)){
        d = list_head(saux->sorted_list);
        if (!set_member(d,s0)){
                s = set_elim(s,d);
        }
        saux->sorted_list = list_tail(saux->sorted_list);
    } 
    saux = set_destroy(saux);
     
    return s;
}

set set_dif(set s, set s0){
    set saux = set_copy(s0);
    type_elem d;

    while (!set_is_empty(saux)){
        d = list_head(saux->sorted_list);
        if (set_member(d,s)){
            s = set_elim(s,d);
        }
        saux->sorted_list = list_tail(saux->sorted_list);   
    }
    saux = set_destroy(saux);
    return s;
}

type_elem set_get(set s){
    assert(!set_is_empty(s));
    int e = list_head(s->sorted_list);
    return e;
}

set set_copy(set s){
    set s0=set_empty();
    s0->sorted_list=list_copy(s->sorted_list);
    return s0;
}

set set_destroy(set s){
    s->sorted_list=list_destroy(s->sorted_list);
    free(s);
    return s;
}