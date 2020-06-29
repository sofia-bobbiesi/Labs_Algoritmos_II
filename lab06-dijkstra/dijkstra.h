#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_

#include "graph.h"
#include "set.h"

/** Dijkstra Algorithm
@param graph A graph represented as a cost matrix (@see graph.h)
@param init The initial vertex

@return An array of costs that contains
	for each position 'v' such that 0 <= 'v' < graph_max_size('graph'),
	the minimum cost of a path from 'init' to 'v' in the 'graph'.

@note The returned array must be freed by the user.
*/
cost_t *dijkstra(graph_t graph, vertex_t init);

/* Function of the star exercise that calculates given a quantity of liters 
and a total of cities, which I can visit based on the preference given*/
set holidays(graph_t graph, vertex_t init, set cities, cost_t litre, type_elem *array_cities);

#endif
