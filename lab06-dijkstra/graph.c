#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
struct graph_data {
    cost_t *costs;
    unsigned int max_size;
};

graph_t graph_empty(unsigned int max_size)
{
    graph_t graph = calloc(1, sizeof(struct graph_data));
    assert(graph != NULL);
    graph->max_size = max_size;
    graph->costs = calloc(max_size * max_size, sizeof(cost_t));
    for (unsigned int i = 0; i < max_size * max_size; ++i) {
        graph->costs[i] = cost_inf();
    }
    assert(graph->costs != NULL);
    return graph;
}

unsigned int graph_max_size(graph_t graph)
{
    assert(graph != NULL);
    return graph->max_size;
}

void graph_add_edge(graph_t graph, vertex_t from, vertex_t to, cost_t cost)
{
    assert(graph != NULL);
    assert(from < graph->max_size);
    assert(to < graph->max_size);
    graph->costs[to + graph->max_size * from] = cost;
}

cost_t graph_get_cost(graph_t graph, vertex_t from, vertex_t to)
{
    assert(graph != NULL);
    assert(from < graph->max_size);
    assert(to < graph->max_size);
    return graph->costs[to + graph->max_size * from];
}

graph_t graph_destroy(graph_t graph)
{
    assert(graph != NULL);
    free(graph->costs);
    free(graph);
    return NULL;
}

void graph_print(graph_t graph)
{
    assert(graph != NULL);
    printf("%u\n", graph->max_size);
    for (unsigned int i = 0; i < graph->max_size; ++i) {
        for (unsigned int j = 0; j < graph->max_size; ++j) {
            const cost_t cost = graph_get_cost(graph, i, j);
            if (cost_is_inf(cost)) {
                printf("# ");
            } else {
                printf("%d ", cost);
            }
        }
        printf("\n");
    }
}

graph_t graph_from_file(const char *file_path)
{
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }
    unsigned int tam = 0;
    fscanf(file, "%u", &tam);
    char word[256];
    const graph_t graph = graph_empty(tam);
    for (unsigned int i = 0; i < tam; ++i) {
        for (unsigned int j = 0; j < tam; ++j) {
            cost_t cost = cost_inf();
            fscanf(file, "%s", word);
            if (word[0] != '#') {
                cost = atoi(word);
            }
            graph_add_edge(graph, i, j, cost);
        }
    }
    fclose(file);
    return graph;
}

graph_t graph_fill(unsigned int graph_size,type_elem array_cities[]){
    char word[256];
    const graph_t graph = graph_empty(graph_size);
    for (unsigned int i = 0; i < graph_size; ++i) {
        for (unsigned int j = 0; j < graph_size; ++j) {
            cost_t cost = cost_inf();
            if (i != j){
                printf("Enter the distance (%d,%d): ",array_cities[i],array_cities[j]);
                scanf("%s", word);
                if (word[0] != '#') {
                    cost = atoi(word);
                }
            }else{
                cost = 0;
            }
            graph_add_edge(graph, i, j, cost);
        }
    }
    return graph;   
}