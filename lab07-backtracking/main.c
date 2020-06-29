#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <limits.h>
#include "helpers.h"
#include "knapsack.h"

#define MAX_FILES 100

void show_usage()
{
    printf("Usage:\n");
    printf("knapsack <option>\n");
    printf("-f <files> Run algorithms on the all the files listed."
           "Stdin is used by default\n");
    printf("-b Enable backtracking algorithm\n");
    printf("-d Enable dynamic algorithm\n");
    printf("-s Show selected items (only in dynamic algorithm)\n");
    printf("-t Enable testing (checks VALUE field on the first line"
            " of each input file)\n");
    printf("-w <arg> Force knapsack capacity to [arg]. ");
    printf("Reads KNAPSACK field on first line of each input file"
           " by default\n\r");
    printf("Example: knapsack -bds -f input/example*.in\n");
}

//open a file with the given name, or select stdin if null.
FILE* open_file(const char* filename)
{
    FILE* file = NULL;
    if (filename == NULL)
    {
        file = stdin;
    }
    else
    {
        file = fopen(filename, "r");
        if (file == NULL)
        {
            fprintf(stderr, "Error opening file %s.\n", filename);
            exit(1);
        }
    }
    return (file);
}

//close file if not stdin
void close_file(FILE* file)
{
    if (file != stdin)
    {
        fclose(file);
    }
}

//parse an unsigned int from a string
unsigned int uint_from_string(const char* str)
{
    char* data = NULL;
    unsigned long int conv = strtoul(str, &data, 10);
    unsigned int res = 0;
    if ((data != NULL && *data != 0) || (conv > UINT_MAX))
    {
        fprintf(stderr, "INVALID UNSIGNED INT (INPUT \"%s\")\n", str);
        exit(1);
    }
    else
    {
        res = (unsigned int) conv;
    }
    return (res);
}

//parse first line of a file. Looks for a line starting with '#'
//then the KNAPSACK field with the desired capacity, and VALUE with the
//expected value.
void parse_first_line(FILE* file, weight_t* weight,value_t* expected, bool* test){
    char* line = readline(file);
    if (line != NULL)
    {
        char* token = strtok(line, " :\t\n");
        if (token != NULL && strcmp(token, "#") == 0)
        {
            char* wtoken = strtok(NULL, " :\t\n");
            if (wtoken != NULL && (strcmp(wtoken, "KNAPSACK") == 0))
            {
                char* w_str = strtok(NULL, " :\t\n");
                if (w_str != NULL && strlen(w_str) > 0)
                {
                    *weight = uint_from_string(w_str);
                }
            }
            wtoken = strtok(NULL, " :\t\n");
            if (wtoken != NULL && (strcmp(wtoken, "VALUE") == 0))
            {
                char* w_str = strtok(NULL, " :\t\n");
                if (w_str != NULL && strlen(w_str) > 0)
                {
                    *expected = uint_from_string(w_str);
                }
            }
            else
            {
                if (*test)
                {
                    printf("-t option expects VALUE field"
                            " in the first line\n");
                    *test = false;
                }
            }
        }
        else
        {
            //no # line, file should point at the beginning.
            rewind(file);
        }
        free(line);
    }
}
/* Order the items in such a way that they are printed according to their value */
static void swap(item_t *x, item_t *y) { 
    item_t temp = *x; 
    *x = *y; 
    *y = temp; 
}

static void bubblesort(item_t *items,unsigned int n){
    if (items != NULL){
       for (unsigned int i = 0; i < n-1; i++){       
            for (unsigned int j = 0; j < n-i-1; j++){ 
                if (item_value(items[j]) < item_value(items[j+1])){
                    swap(&items[j], &items[j+1]);
                }
            }
        }
    }
}

//execute algorithms on the given file.
int run_file(const char* filename, bool do_backtracking, bool do_dynamic, bool show_items, bool test,weight_t weight){
    FILE* file = NULL;
    int fails = 0;
    value_t expected = 0;
    unsigned int array_length = 0u;
    file = open_file(filename);
    if (file != stdin)
    {
        //if not stdin, parse first line, starting with #
        weight_t aux = 0;
        parse_first_line(file, &aux, &expected, &test);
        if (weight == 0)   //not -w option, or -w 0.
        {
            printf("Reading KNAPSACK capacity from file...\n");
            weight = aux;
        }
    }
    printf("Reading ITEMS from %s...\n", file == stdin ? "stdin" : "file");
    item_t* items = item_read_from_file(file, &array_length);
    close_file(file);
    printf("Knapsack capacity: %u\n", weight);
    printf("Items: %u\n", array_length);
    value_t backtracking_value = 0;
    if (do_backtracking)
    {
        //if backtracking is enabled, run it.
        printf("Backtracking solution...\n");
        value_t value = knapsack_backtracking(items, array_length, weight);
        printf("Value: %u\n", value);
        if (test)
        {
            printf("Test - Value matches expected: %s\n",value == expected ? "OK" : "FAIL");
            fails = fails + (value == expected ? 0 : 1);
        }
        backtracking_value = value;
    }
    if (do_dynamic)
    {
        //if dynamic is enabled, run it.
        printf("Dynamic solution...\n");
        value_t value = 0;
        if (show_items)
        {
            //if items are requested, run knapsack_dynamic_selection
            bool* selected = calloc(array_length, sizeof(bool));
            if (selected == NULL)
            {
                fprintf(stderr, "No more memory available!\n");
                exit(1);
            }
            bubblesort(items,array_length);
            value = knapsack_dynamic_selection(items, selected, array_length,weight);
            printf("Selected items:\n");
            value_t total = 0;
            weight_t sum = 0;
            for (unsigned int i = 0u; i < array_length; i++)
            {
                if (selected[i])
                {
                    //if selected, print it.
                    item_t item = items[i];
                    total = total + item_value(item);
                    sum = sum + item_weight(item);
                    printf("%s:%u:%u\n", string_ref(item_id(item)),item_value(item),item_weight(item));
                }
            }
            if (test)
            {
                printf("Test - Selected items value: %s\n", total == value ? "OK" : "FAIL");
                printf("Test - Selected items weight: %s\n", sum <= weight ? "OK" : "FAIL");
                fails = fails + (sum <= weight ? 0 : 1);
                fails = fails + (total == value ? 0 : 1);
            }
            free(selected);
            selected = NULL;
        }
        else
        {
            //items are not requested, use knapsack_dynamic algorithm
            value = knapsack_dynamic(items, array_length, weight);
        }
        printf("Value: %d\n", value);
        if (test)
        {
            printf("Test - Value matches expected: %s\n", value == expected ? "OK" : "FAIL");
            fails = fails + (value == expected ? 0 : 1);
            if (do_backtracking)
            {
                printf("Test - Matches backtracking value: %s\n", value == backtracking_value ? "OK" : "FAIL");
                fails = fails + (value == backtracking_value ? 0 : 1);
            }
        }
    }
    //destroy items
    for (unsigned int i = 0; i < array_length; i++)
    {
        items[i] = item_destroy(items[i]);
    }
    free(items);
    return (fails);
}

bool is_option(const char* str)
{
    return (*str == '-' && strlen(str) == 2);
}

int main(int argc, char** argv)
{
    char* filenames[MAX_FILES];
    int option = 0;
    bool do_backtracking = false;
    bool do_dynamic = false;
    bool show_items = false;
    bool test = false;
    unsigned int weight = 0u;
    unsigned int files_count = 0u;
    if (argc == 1)
    {
        show_usage();
        exit(EXIT_FAILURE);
    }
    while ((option = getopt(argc, argv, "f:w:sbdt")) != -1)
    {
        switch (option)
        {
            case 'b':
                do_backtracking = true;
                break;
            case 'd':
                do_dynamic = true;
                break;
            case 's':
                show_items = true;
                break;
            case 'f':
                optind--;
                while (optind < argc && !is_option(argv[optind]) && files_count < MAX_FILES){
                    files_count++;
                    filenames[files_count - 1] = argv[optind];
                    optind++;
                }
                break;
            case 'w':
                weight = uint_from_string(optarg);
                break;
            case 't':
                test = true;
                break;
            case '?':
                show_usage();
                exit(EXIT_FAILURE);
                break;
            default:
                break;
        }
    }
    if (files_count == 0u){
        filenames[0] = NULL;
        files_count = 1;
        test = false;
    }
    int fails = 0;
    for (unsigned int i = 0u; i < files_count; ++i)
    {
        printf("READING %s\n", filenames[i] == NULL ? "stdin" : filenames[i]);
        fails = run_file(filenames[i], do_backtracking, do_dynamic, show_items, test, weight);
        printf("DONE %s.\n\n", filenames[i] == NULL ? "stdin" : filenames[i]);
    }
    if (fails > 0 && test)
    {
        printf("\n\n FAILS: %d \n\n", fails);
    }
    else if (test)
    {
        printf("\n\n ALL TESTS OK \n\n");
    }
    return EXIT_SUCCESS;
}
