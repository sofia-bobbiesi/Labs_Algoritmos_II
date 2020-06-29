#include <stdbool.h>
#include <stdlib.h>
#include "item.h"

static value_t max_value(value_t x, value_t y){ 
	return x >= y ? x : y;
}

value_t knapsack_backtracking(item_t* items, unsigned int array_length, weight_t max_weight){
    value_t res;
    /* First and second case: j==0 || j>0 && i==0 */
    if(array_length == 0 || max_weight == 0){
        res = 0;
    }
    else{
        /* Initialize the item in the last element */
        item_t item = items[array_length-1];
        /* Third case: knapsack(i-1,j) if wi>j>0 && i>0 */
        if (item_weight(item)>max_weight){
            res = knapsack_backtracking(items, array_length-1,max_weight);
        }
        /* Fourth case: max(knpasack(i-1,j),vi+knapsack(i-1,j-wi)) if j>=wi>0 && i>0 */
        else{
            value_t not_keeping = knapsack_backtracking(items, array_length-1,max_weight);
            value_t keeping = item_value(item) + knapsack_backtracking(items, array_length-1,max_weight-item_weight(item));
            res = max_value(not_keeping, keeping);
        }
    }
    return res;
}

value_t knapsack_dynamic(item_t* items, unsigned int array_length, weight_t max_weight){
    value_t **board = calloc(array_length+1,sizeof(value_t*));
    /* Initialize the array by rows and by columns */
    for (unsigned int i = 0u; i < array_length+1; i++){
        board[i] = calloc(max_weight+1,sizeof(value_t));
    }
    /* First case: (0 if j == 0) and Second case: (0 if j>0 && i==0) 
    are covered through the use of calloc */

    /* Third case: knapsack(i-1,j) if wi>j>0 && i>0 */
    for (unsigned int i = 1u; i <= array_length; i++){
        for (unsigned int j = 1u; j <= max_weight; j++){
            /* Third case: knapsack(i-1,j) if wi>j>0 && i>0 */
            if (item_weight(items[i-1])>j){
                board[i][j] = board[i-1][j];
            }
            /* Fourth case: max(knpasack(i-1,j),vi+knapsack(i-1,j-wi)) if j>=wi>0 && i>0 */
            else{
                board[i][j] = max_value(board[i-1][j], item_value(items[i-1]) + board[i-1][j-item_weight(items[i-1])]);
            }
        }
    }
    value_t res = board[array_length][max_weight];
   /* Destroy the board */
    for (unsigned int i = 0u; i < array_length+1; i++){
        free(board[i]);
    }
    free(board);
    return res;
}

value_t knapsack_dynamic_selection(item_t* items, bool* selected, unsigned int array_length, weight_t max_weight){
    value_t **board = calloc(array_length+1,sizeof(value_t*));
    /* Initialize the array by rows and by columns */
    for (unsigned int i = 0u; i < array_length+1; i++){
        board[i] = calloc(max_weight+1,sizeof(value_t));
    }
    /* First case: (0 if j == 0) and Second case: (0 if j>0 && i==0) 
    are covered through the use of calloc */

    /* Third case: knapsack(i-1,j) if wi>j>0 && i>0 */
    for (unsigned int i = 1u; i <= array_length; i++){
        for (unsigned int j = 1u; j <= max_weight; j++){
            /* Third case: knapsack(i-1,j) if wi>j>0 && i>0 */
            if (item_weight(items[i-1])>j){
                board[i][j] = board[i-1][j];
            }
            /* Fourth case: max(knpasack(i-1,j),vi+knapsack(i-1,j-wi)) if j>=wi>0 && i>0 */
            else{
                board[i][j] = max_value(board[i-1][j], item_value(items[i-1]) + board[i-1][j-item_weight(items[i-1])]);
            }
        }
    }
    value_t res = board[array_length][max_weight];

    /* Implementation of the floyd algorithm to fill the selected array */
    unsigned int r = array_length;
    weight_t s = max_weight;

    while (board[r][s] > 0){
        if(board[r][s] == board[r-1][s]){
            selected[r-1] = false;
        }
        else{
            selected[r-1] = true;
            s = s - item_weight(items[r-1]);
        }
        r--;
    }

    /* Destroy the board */
    for (unsigned int i = 0u; i < array_length+1; i++){
        free(board[i]);
    }
    free(board);
    return res;
}