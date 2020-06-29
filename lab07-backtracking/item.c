#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "item.h"
#include "helpers.h"
#include "string.h"

struct _item
{
    string_t id;
    value_t value;
    weight_t weight;
};

item_t item_create(string_t id, value_t value, weight_t weight)
{
    item_t item = calloc(1, sizeof(struct _item));
    assert(item != NULL);
    item->id = id;
    item->value = value;
    item->weight = weight;
    return (item);
}

value_t item_value(item_t item)
{
    assert(item != NULL);
    return (item->value);
}

weight_t item_weight(item_t item)
{
    assert(item != NULL);
    return (item->weight);
}

string_t item_id(item_t item)
{
    assert(item != NULL);
    return (item->id);
}

item_t item_destroy(item_t item)
{
    assert(item != NULL);
    item->id = string_destroy(item->id);
    free(item);
    item = NULL;
    return (item);
}

static unsigned int uint_from_string(const char* str)
{
    char* data = NULL;
    unsigned long int conv = strtoul(str, &data, 10);
    unsigned int res = 0;
    if ((data != NULL && *data != 0) || (conv > UINT_MAX))
    {
        fprintf(stderr, "INVALID UNSIGNED INT (INPUT %s)\n", str);
        exit(1);
    }
    else
    {
        res = (unsigned int) conv;
    }
    return (res);
}

item_t* item_read_from_file(FILE* file, unsigned int* array_length)
{
    assert(file != NULL);
    char* line = NULL;
    item_t* items = NULL;
    unsigned int count = 0u;
    while ((line = readline(file)) != NULL)
    {
        const char* blank = ": \n\t";
        char* id = strtok(line, blank);
        char* value_str = strtok(NULL, blank);
        char* weight_str = strtok(NULL, blank);
        if (value_str != NULL && weight_str != NULL)
        {
            value_t value  = uint_from_string(value_str);
            weight_t weight = uint_from_string(weight_str);
            ++count;
            //improve me: too many realloc calls.
            items = realloc(items, count * sizeof(item_t));
            assert(items != NULL);
            items[count - 1] = item_create(string_create(id), value, weight);
        }
        else
        {
            fprintf(stderr, "SYNTAX ERROR: (wrong line = \"%s\")\n", line);
            exit(EXIT_FAILURE);
        }
        free(line);
    }
    *array_length = count;
    return (items);
}
