#include <stdio.h>
#include <stdlib.h>
#include "set.h"
#include <string.h>
#include <limits.h>
#include "dijkstra.h"

set set_fill(set cities,unsigned int size){
    for (unsigned int i = 0u; i < size; i++){
        type_elem input;
        printf("Enter the city %u: ",i+1);
        scanf("%d",&input);
        cities = set_add(cities,input);
    }
    return cities;
}

type_elem *set_to_array(set s0) {
    unsigned int length = set_cardinal(s0);
    type_elem *set_array = calloc(length, (sizeof(type_elem)));
    set s0_copy = set_copy(s0);
    unsigned int i = 0;
    while(!set_is_empty(s0_copy) && i < length){
        type_elem curr = set_get(s0_copy);
        set_array[i] = curr;
        i++;
        s0_copy = set_elim(s0_copy, curr);
    }
    s0_copy = set_destroy(s0_copy);
    return set_array;
}

int main(){
 
    cost_t litres;
    printf("Enter the maximum of liters of gasoline: ");
    scanf("%d",&litres);

    unsigned int num_cities;
    printf("Enter the number of total cities: ");
    scanf("%u",&num_cities);

    /* Fill the set with the cities */
    set cities = set_empty();
    cities = set_fill(cities,num_cities);

    unsigned int num_cities_to_visit;
    printf("Enter the number of cities to visit: ");
    scanf("%u",&num_cities_to_visit);

    /* Fill the set with the cities */
    set cities_to_visit = set_empty();
    cities_to_visit = set_fill(cities_to_visit,num_cities_to_visit);

    /* Make sure that the cities to visit are in the total of cities 
    for some reason, set_inters is not working properly */
    set visit_copy = set_copy(cities_to_visit);
    while(!set_is_empty(visit_copy)){
        type_elem curr = set_get(visit_copy);
        if (!set_member(curr, cities)){
            /* Clean unavailable cities */
           cities_to_visit = set_elim(cities_to_visit, curr);
        }
        visit_copy = set_elim(visit_copy, curr);
    }
    visit_copy = set_destroy(visit_copy);
    
    type_elem *array_cities = set_to_array(cities);

    int init_aux;
    printf("Enter the city of start: ");
    scanf("%d",&init_aux);
    while(!set_member(init_aux,cities)&&(init_aux<0)){
            printf("Non-existent city please enter another: ");
            scanf("%d",&init_aux);
    }
    /* Find the vertex of the city */
    vertex_t init;
    for (unsigned int i = 0; i < num_cities; i++){
        if (array_cities[i]==init_aux){
            init = i;
        } 
    }

    /* Fill the graph with the cost of the trips */
    graph_t graph = graph_fill(num_cities,array_cities);

    set final_cities = holidays(graph,init,cities,litres,array_cities);

    while(!set_is_empty(final_cities)){
        type_elem e = set_get(final_cities);
        printf("\nYou can reach the city %d\n",array_cities[e]);
        final_cities = set_elim(final_cities, e);
    }
    cities=set_destroy(cities);
    cities_to_visit=set_destroy(cities_to_visit);
    final_cities=set_destroy(final_cities);
    free(array_cities);
    graph=graph_destroy(graph);

    return 0;
}