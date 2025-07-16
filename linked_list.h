#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "raylib.h"

/**
 * The data type stored in each node of the list.
 * 
 * Raylib Vector2 definition:
 *     float x
 *     float y
 */
typedef Vector2 list_type;

/**
 * Node definition:
 *      elem: The current node's element
 *      next: A pointer to the next of the current node 
 */
typedef struct node {
    list_type elem;
    struct node* next;
} Node;

/**
 * List definition: A pointer to the first node of the list
 */
typedef Node* List;

/**
 * Initializes a new list.
 */
void init_list(List *);

/**
 * Appends the element at the end of the given list.
 */
void append(List *, list_type);

/**
 * Checks if the element is contained in the given list and returns the result.
 */
bool contains(List, list_type);

/**
 * Deletes the element from the given list if it's contained.
 */
void remove_element(List *, list_type);

/**
 * Checks if the given list has no elements and returns the result.
 */
bool is_empty(List);

/**
 * Prints the stored values of the given list in console.
 */
void print_list(List);

/**
 * Frees the memory allocated for the nodes of the given list.
 */
void free_list(List *);

#endif