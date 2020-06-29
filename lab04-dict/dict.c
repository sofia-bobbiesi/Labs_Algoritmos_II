#include <assert.h>
#include "dict.h"
#include "key_value.h"
#include <stdlib.h>
#include <stdbool.h>

struct _node_t {
    dict_t left;
    dict_t right;
    key_t key;
    value_t value;
    unsigned int length;
};

dict_t dict_empty() {
        /* Initializing of dict */
        dict_t dict = NULL;
        return dict;
}

static dict_t dict_create_node(key_t word, value_t def){
        /* We assing memory if the dict is empty or if
        we are in a new node */
        dict_t dict = (dict_t)malloc(sizeof(struct _node_t));
        /* Just point to the input values */
        dict->key=word;
        dict->value=def;
        /* Initializing of length */
        dict->length = 1;
        /* Initialize the corresponding sub trees */
        dict->left=dict_empty(); 
        dict->right=dict_empty();
    return dict;
}

dict_t dict_add(dict_t dict, key_t word, value_t def) {
    assert(word != NULL && def != NULL);
    bool duplicate = dict_exists(dict,word);
    if(dict==NULL){
        dict = dict_create_node(word,def);
    }
    else {
        if(key_less(dict->key,word)){
            /* If the key entered is greater than the current
            one, then it is to the right */
            if (!duplicate){
               dict->length++;
            }
            dict->right = dict_add(dict->right,word,def);
        }
        else if(key_less(word,dict->key)){
            /* If the key entered is less than the current
            one, then it is to the left */
            if (!duplicate){
               dict->length++;
            }
            dict->left = dict_add(dict->left,word,def);
        }   
        else{ 
            /* if the key entered is not minor, is not greater
            and is not null, then it is equal. In this case,
            we only redefine the value */
            dict->value = value_destroy(dict->value);
            dict->value=def;
        }
    }
    assert(value_eq(def, dict_search(dict, word)));
    return dict;
}

value_t dict_search(dict_t dict, key_t word) {
    assert(word != NULL);
    value_t def = NULL; 
   
    if (dict !=NULL ){ 
        /* Same logical estructure as dict_add */
        if (key_eq(dict->key,word)){
            def = dict->value;
        }
        else if (key_less(word,dict->key)){
            def = dict_search(dict->left,word);
        } 
        else {
            /* if it is not minor and is not equal, then it is greater */
            def = dict_search(dict->right,word);
            }
        } 
    return def;
}

bool dict_exists(dict_t dict, key_t word) {
    assert(word != NULL);
    bool exists = false;
    if (dict != NULL){
        /* At least one should be true. So... */
        exists = key_eq(dict->key,word) || dict_exists(dict->left,word) || dict_exists(dict->right,word);
    }
    return exists;
}
/* Returns the length by recursive methode
unsigned int dict_length(dict_t dict){
    unsigned int length = 0u;
    if (dict !=NULL){
        length = dict_length(dict->left) + 1 + dict_length(dict->right); 
    }
    return length;
}
*/
unsigned int dict_length(dict_t dict){
    unsigned int length = 0u;
    if (dict!=NULL){
        length = dict->length;
    }
    return length;
}
/* Recursive method to finde the minimum node:  
 * PRE: {dict -> dict}
 *  dict = dict_min_node(dict);
 * POS: {dict --> dict /\ dict_length(dict) == 1}
*/

static dict_t dict_min_node(dict_t dict){
    dict_t min = NULL;
    /* Just keep moving left until we arrive at the min */
    if(dict->left!=NULL){
        min = dict_min_node(dict->left);
    }
    else{
        min = (dict_t)malloc(sizeof(struct _node_t));
        /* I couldn’t solve this without using clone, sorry */
        min->key = key_clone(dict->key);
        min->value = value_clone(dict->value); 
    }
    return min;
} 

dict_t dict_remove(dict_t dict, key_t word) {
    assert(word != NULL);
    /* Same logical estructure as dict_add */
    if(dict!=NULL){
        if (key_less(word,dict->key)){ 
            dict->left = dict_remove(dict->left,word);
            dict->length--;
        } 
        else if(key_less(dict->key,word)){
            dict->right = dict_remove(dict->right,word); 
            dict->length--;
        } 
        else {
            /* Case 1: No children */
            if ((dict->left==NULL)&&(dict->right==NULL)){
                dict->key = key_destroy(dict->key);
                dict->value = value_destroy(dict->value);
                free(dict);
                dict = NULL;
            }
            /* Case 2: One right child */
            else if (dict->left==NULL){
                dict_t daux = dict;
                /* Reconnect the dict and remove the node */
                dict = dict->right;
                daux->key = key_destroy(daux->key);
                daux->value = value_destroy(daux->value);
                free(daux);
                
            } 
            /* Case 3: One left child */
            else if(dict->right==NULL){
                dict_t daux = dict;
                /* Reconnect the dict and remove the node */
                dict = dict->left;
                daux->key = key_destroy(daux->key);
                daux->value = value_destroy(daux->value);
                free(daux);
            }
            /* Cse 4: Two childrens */
            else {
                /* Find a new root that will be the least right node */
                dict_t daux = dict_min_node(dict->right);
                /* Destroy and reset the node values to avoid dangling pointers*/
                dict->key = key_destroy(dict->key);
                dict->value = value_destroy(dict->value);
                dict->key = daux->key;
                dict->value = daux->value;
                /* Remove the branch with the value [key,def] of the
                node as it will now be the new root */
                dict->right = dict_remove(dict->right,daux->key);
                dict->length--;
                free(daux); 
            }
        }
    }
    return dict;
} 

dict_t dict_remove_all(dict_t dict) {
    if (dict !=NULL){
        /* Just remove those all nodes */
        dict->key = key_destroy(dict->key);
        dict->value = value_destroy(dict->value);
        dict->left = dict_remove_all(dict->left);
        dict->right = dict_remove_all(dict->right);
        free(dict);
        dict = NULL;
    }  
    return dict;
}

void dict_dump(dict_t dict, FILE *file) {
    assert(file != NULL);
    if (dict != NULL && file != stdout) {
        /* Print PreOrder: The first element is the root,
        then print the left branch and then the right branch. */
        key_dump(dict->key, file);
        fprintf(file, ": ");
        value_dump(dict->value, file);
        fprintf(file, "\n");
        dict_dump(dict->left, file);
        dict_dump(dict->right, file);
    } 
    else if (dict != NULL && file == stdout){
        /* Print InOrder: The root is located in the middle,
        the elements on the left subtree are above and the
        elements on the right subtree, below. */
        dict_dump(dict->left, file);
        key_dump(dict->key, file);
        fprintf(file, ": ");
        value_dump(dict->value, file);
        fprintf(file, "\n");
        dict_dump(dict->right, file);
        
    }
}

dict_t dict_destroy(dict_t dict) {
    if (dict !=NULL){
        /* Just destroy those all memory */
        dict->key = key_destroy(dict->key);
        dict->value = value_destroy(dict->value);
        dict->left=dict_destroy(dict->left);
        dict->right=dict_destroy(dict->right);
        free(dict);
    } 
    return NULL;
}