#ifndef ITEM_H
#define ITEM_H
#include <stdbool.h>
#include "string.h"

typedef struct _item* item_t;
typedef unsigned int weight_t;
typedef unsigned int value_t;

/** Creates an item
* @param id item's name
* @param value item's value
* @param weight item's weight
* @return a new item
**/
item_t item_create(string_t id, value_t value, weight_t weight);

/** Returns item's value
* @param item an item
* @return item's value
**/
value_t item_value(item_t item);

/** Returns item's weight
* @param item an item
* @return item's weight
**/
weight_t item_weight(item_t item);

/** Returns item's id
* @param item an item
* @return item's name
**/
string_t item_id(item_t id);

/** Returns a dynamic array of items obtained from a file. Stores
* the length of the array in *array_length
* @param file a text file describing items
* @param[out] array_length amount of obtained items
* @return an array of items
**/
item_t* item_read_from_file(FILE* file, unsigned int* array_length);

/** Destroys the item
* @param item an item
**/
item_t item_destroy(item_t item);

#endif
