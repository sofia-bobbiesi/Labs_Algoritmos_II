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
};

struct _dict_t{
   size_t length;
   struct _node_t *root;
};

dict_t dict_empty() {
        /* Initializing of dict */
        dict_t dict = malloc(sizeof(struct _dict_t));
        dict->length = 0;
        dict->root=NULL;
        return dict;
}

static dict_t dict_create_node(dict_t dict, key_t word, value_t def){
        /* We assing memory if the dict is empty or if
        we are in a new node */
        node_t root = malloc(sizeof(struct _node_t));
        /* Just point to the input values */
        dict->root->key=word;
        dict->root->value=def;
        /* Initialize the corresponding sub trees */
        dict->root->left=dict_empty(); 
        dict->root->right=dict_empty();
    return dict;
}

dict_t dict_add(dict_t dict, key_t word, value_t def) {
    assert(word != NULL && def != NULL && dict!=NULL);
    if(dict->root==NULL){
        dict = dict_create_node(dict,word,def);
    }
    else {
        if(key_less(dict->root->key,word)){
            /* If the key entered is greater than the current
            one, then it is to the right */
            dict->length++; 
            dict->root->right = dict_add(dict->root->right,word,def);
        }
        else if(key_less(word,dict->root->key)){
            /* If the key entered is less than the current
            one, then it is to the left */
            dict->length++;
            dict->root->left = dict_add(dict->root->left,word,def);
        }   
        else{ 
            /* if the key entered is not minor, is not greater
            and is not null, then it is equal. In this case,
            we only redefine the value */
            dict->root->value = value_destroy(dict->root->value);
            dict->root->value=def;
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
        if (key_eq(dict->root->key,word)){
            def = dict->root->value;
        }
        else if (key_less(word,dict->root->key)){
            def = dict_search(dict->root->left,word);
        } 
        else {
            /* if it is not minor and is not equal, then it is greater */
            def = dict_search(dict->root->right,word);
            }
        } 
    return def;
}

bool dict_exists(dict_t dict, key_t word) {
    assert(word != NULL);
    bool exists = false;
    if (dict != NULL){
        /* At least one should be true. So... */
        exists = key_eq(dict->root->key,word) || dict_exists(dict->root->left,word) || dict_exists(dict->root->right,word);
    }
    return exists;
}

size_t dict_length(dict_t dict){
    return dict->length;
}
/* Recursive method to finde the minimum node:  
 * PRE: {dict -> dict}
 *  dict = dict_min_node(dict);
 * POS: {dict --> dict /\ dict_length(dict) == 1}
*/

static dict_t dict_min_node(dict_t dict){
    dict_t min = NULL;
    /* Just keep moving left until we arrive at the min */
    if(dict->root->left!=NULL){
        min = dict_min_node(dict->root->left);
    }
    else{
        min = (dict_t)malloc(sizeof(struct _node_t));
        /* I couldn’t solve this without using clone, sorry */
        min->root->key = key_clone(dict->root->key);
        min->root->value = value_clone(dict->root->value); 
    }
    return min;
} 

dict_t dict_remove(dict_t dict, key_t word) {
    assert(word != NULL);
    /* Same logical estructure as dict_add */
    if(dict!=NULL){
        if (key_less(word,dict->root->key)){ 
            dict->root->left = dict_remove(dict->root->left,word);
            dict->length--;
        } 
        else if(key_less(dict->root->key,word)){
            dict->root->right = dict_remove(dict->root->right,word); 
            dict->length--;
        } 
        else {
            /* Case 1: No children */
            if ((dict->root->left==NULL)&&(dict->root->right==NULL)){
                dict->root->key = key_destroy(dict->root->key);
                dict->root->value = value_destroy(dict->root->value);
                free(dict);
                dict = NULL;
            }
            /* Case 2: One right child */
            else if (dict->root->left==NULL){
                dict_t daux = dict;
                /* Reconnect the dict and remove the node */
                dict = dict->root->right;
                daux->root->key = key_destroy(daux->root->key);
                daux->root->value = value_destroy(daux->root->value);
                free(daux);
                
            } 
            /* Case 3: One left child */
            else if(dict->root->right==NULL){
                dict_t daux = dict;
                /* Reconnect the dict and remove the node */
                dict = dict->root->left;
                daux->root->key = key_destroy(daux->root->key);
                daux->root->value = value_destroy(daux->root->value);
                free(daux);
            }
            /* Cse 4: Two childrens */
            else {
                /* Find a new root that will be the least right node */
                dict_t daux = dict_min_node(dict->root->right);
                /* Destroy and reset the node values to avoid dangling pointers*/
                dict->root->key = key_destroy(dict->root->key);
                dict->root->value = value_destroy(dict->root->value);
                dict->root->key = daux->root->key;
                dict->root->value = daux->root->value;
                /* Remove the branch with the value [key,def] of the
                node as it will now be the new root */
                dict->root->right = dict_remove(dict->root->right,daux->root->key);
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
        dict->root->key = key_destroy(dict->root->key);
        dict->root->value = value_destroy(dict->root->value);
        dict->root->left = dict_remove_all(dict->root->left);
        dict->root->right = dict_remove_all(dict->root->right);
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
        key_dump(dict->root->key, file);
        fprintf(file, ": ");
        value_dump(dict->root->value, file);
        fprintf(file, "\n");
        dict_dump(dict->root->left, file);
        dict_dump(dict->root->right, file);
    } 
    else if (dict != NULL && file == stdout){
        /* Print InOrder: The root is located in the middle,
        the elements on the left subtree are above and the
        elements on the right subtree, below. */
        dict_dump(dict->root->left, file);
        key_dump(dict->root->key, file);
        fprintf(file, ": ");
        value_dump(dict->root->value, file);
        fprintf(file, "\n");
        dict_dump(dict->root->right, file);     
    }
}

dict_t dict_destroy(dict_t dict) {
    if (dict->root !=NULL){
        /* Just destroy those all memory */
        dict->root->key = key_destroy(dict->root->key);
        dict->root->value = value_destroy(dict->root->value);
        dict->root->left=dict_destroy(dict->root->left);
        dict->root->right=dict_destroy(dict->root->right);
        free(dict);
    } 
    return NULL;
}