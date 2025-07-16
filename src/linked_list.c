#include "linked_list.h"
#include "raymath.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Initializes a new list.
 */
void init_list(List *ll) {
    *ll = NULL;
}

/**
 * Appends the element at the end of the given list.
 */
void append(List *ll, list_type e) {
    Node *new_node = (Node *)malloc(sizeof(Node));

    if (new_node == NULL) {
        return;
    }

    new_node->elem = e;
    new_node->next = NULL;

    if (is_empty(*ll)) { 
        *ll = new_node;
    }
    else {
        Node *aux = *ll;

        while (aux->next != NULL) {
            aux = aux->next;
        }

        aux->next = new_node;
    }
}

/**
 * Checks and returns if the element is contained the given list.
 */
bool contains(List ll, list_type e) {
    if (is_empty(ll)) 
        return false;
    
    Node *aux = ll;
    
    while (aux != NULL) {
        if (Vector2Equals(aux->elem, e)) return true;
        aux = aux->next;
    }
    return false;
}

/**
 * Deletes the element from the given list. 
 */
void remove_element(List *ll, list_type e) {
    if (is_empty(*ll)) {
        return;
    }

    if (Vector2Equals((*ll)->elem, e)) {
        Node *aux = *ll;
        *ll = (*ll)->next;
        free(aux);
    }
    else {
        if ((*ll)->next == NULL) {
            return;
        }

        Node *prev = *ll;
        Node *aux = (*ll)->next;
        
        while (aux->next != NULL && !Vector2Equals(aux->elem, e)) {
            prev = aux;
            aux = aux->next;
        }

        if (Vector2Equals(aux->elem, e)) {
            prev->next = aux->next;
            free(aux);
        }
    }
}

/**
 * Checks and returns if the given list has no elements.
 */
bool is_empty(List ll) {
    return ll == NULL;
}

/**
 * Prints the stored values of the given list in console.
 */
void print_list(List ll) {
    if (is_empty(ll)) return;

    Node *aux = ll;

    while (aux != NULL) {
        printf("(%f, %f) ", aux->elem.x, aux->elem.y);
        aux = aux->next;
    }
    printf("\n");
}

/**
 * Frees the memory allocated for the nodes of the the given list.
 */
void free_list(List *ll) {
    if (is_empty(*ll)) {
        return;
    }

    Node *aux;

    while (!is_empty(*ll)) {
        aux = *ll;
        *ll = (*ll)->next;
        free(aux);
    }

    *ll = NULL;
}