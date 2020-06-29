#ifndef KNAPSACK_H
#define KNAPSACK_H
#include <stdbool.h>
#include "item.h"


/** Knapsack Problem solved with Backtracking
* @param items Available items
* @param array_length Items array length
* @param max_weight  Knapsack maximum weight
* @return Maximum value obtained without exceeding knapsack capacity
**/
value_t knapsack_backtracking(item_t* items, unsigned int array_length, weight_t max_weight);


/** Knapsack Problem solved with Dynamic Programming
* @param items Available items
* @param array_length Items array length
* @param max_weight  Knapsack maximum weight
* @return Maximum value obtained without exceeding knapsack capacity
**/
value_t knapsack_dynamic(item_t* items, unsigned array_length, weight_t max_weight);



/** Knapsack Problem solved with Dynamic Programming
* @param items Available items
* @param[out] selected Boolean array indicating whether an item is selected to
* be inserted in the knapsack
* @param array_length Items array length
* @param max_weight  Knapsack maximum weight
* @return Maximum value obtained without exceeding knapsack capacity
**/
value_t knapsack_dynamic_selection(item_t* items, bool* selected, unsigned int array_length, weight_t max_weight);

#endif

