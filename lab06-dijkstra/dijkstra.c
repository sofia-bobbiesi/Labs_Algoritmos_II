#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "cost.h"
#include "graph.h"
#include "set.h"

/* Selects element 'c' from set s0 such that cost_array[c] is the minimum */
static vertex_t select_min_cost(set s0, cost_t *cost_array) {
    set saux = set_copy(s0);
    cost_t min = cost_inf();
	vertex_t min_vert = 0;
	
    while(!set_is_empty(saux)){
		vertex_t d = set_get(saux);
          if (cost_le(cost_array[d],min)){
              min = cost_array[d];
			  min_vert = d;
          }
          saux = set_elim(saux,d);
    }
	saux = set_destroy(saux);
	return min_vert;
}

static vertex_t min(vertex_t x, vertex_t y){ 
	return cost_le(x,y) ? x : y;
}

cost_t *dijkstra(graph_t graph, vertex_t init) {
	cost_t cost = 0;
	unsigned int graph_size = graph_max_size(graph);
	cost_t sum_costs = 0;
	set saux;	
	/* Create the costs array, which contains all the costs from the vertexes */	
	cost_t *cost_array = calloc(graph_size, (sizeof(cost_t)));

	/* Set s0 contains all the graph's vertexes (except for the init one) */
	set s0 = set_empty();
	for (unsigned int  j = 0u; j < graph_size; j++) {
		s0 = set_add(s0,j);
		cost_array[j] = graph_get_cost(graph, init, j);
	}
	s0 = set_elim(s0, init);

	while(!set_is_empty(s0)) {	
		cost = select_min_cost(s0, cost_array);
		s0 = set_elim(s0, cost);
		saux = set_copy(s0);

		while(!set_is_empty(saux)) {
			vertex_t n = set_get(saux);
			sum_costs = cost_sum(cost_array[cost], graph_get_cost(graph, cost, n)); 
			cost_array[n] = min(cost_array[n], sum_costs);
			saux = set_elim(saux,n);
		}	
		saux = set_destroy(saux);
		
	}
	s0 = set_destroy(s0);
	return cost_array;
}

/* Function that is part of the star exercise */
set holidays(graph_t graph, vertex_t init, set cities, cost_t litre, type_elem *array_cities){
    set chosen_cities = set_empty();
    unsigned int graph_size = graph_max_size(graph); 
    cost_t *cost_for_cities = dijkstra(graph,init);

    for (unsigned int i = 0u; i < graph_size; i++){
        if (cost_le(cost_for_cities[i],litre) && set_member(array_cities[i],cities)){
			chosen_cities = set_add(chosen_cities,i);

        }
    }
	free(cost_for_cities);
	return chosen_cities;
}
