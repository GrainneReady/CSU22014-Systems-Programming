#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// include the header files with the declarations of listset
#include "listset.h"

// create a new, empty linked list set
struct listset * listset_new() {
    struct listset *new_list = malloc(sizeof(struct listset));
    new_list -> head = NULL;
    return new_list;
}

/* check to see if an item is in the set
   returns 1 if in the set, 0 if not */
int listset_lookup(struct listset * this, char * item) {
    for (struct listnode * current_node = this -> head; current_node != NULL; current_node = current_node -> next)
    {
        if (strcmp(current_node -> str, item) == 0) // strcmp returns 0 if equal
            return 1;
    }
    return 0;
}

// add an item, with number 'item' to the set
// has no effect if the item is already in the set.
// New items that are not already in the set should
// be added to the start of the list
void listset_add(struct listset * this, char * item) {
    if (listset_lookup(this, item) == 0)
    {
        struct listnode * new_head = malloc(sizeof(struct listnode));
        new_head -> str = item;
        new_head -> next = this -> head;
        this -> head = new_head;
    }
}

// need to keep previous node
// remove an item with number 'item' from the set
void listset_remove(struct listset * this, char * item) {
    struct listnode * current = malloc(sizeof(struct listnode));
    current = this -> head;
    if (strcmp(current -> str, item) == 0)
    {
        this -> head = current -> next;
    }
    else {
        struct listnode * previous = malloc(sizeof(struct listnode));
        for(previous = this -> head; current != NULL; current = current -> next)
        {
            if (strcmp(current -> str, item) == 0)
            {
                previous -> next = current -> next;
                return; // Early return since item will be successfully removed, no longer need to loop through values
            }
            previous = current;
        }
    }
}
  
// place the union of src1 and src2 into dest
void listset_union(struct listset * dest, struct listset * src1,
		   struct listset * src2) {
    struct listnode * srcCurrent = malloc(sizeof(struct listnode));
    for (srcCurrent = src1 -> head; srcCurrent != NULL; srcCurrent = srcCurrent -> next)
    {
        listset_add(dest, srcCurrent -> str);
    }
    for (srcCurrent = src2 -> head; srcCurrent != NULL; srcCurrent = srcCurrent -> next)
    {
        if (listset_lookup(dest, srcCurrent -> str) == 0) // Lookup to check if an item is already in dest so we don't put the same item in twice
        {
            listset_add(dest, srcCurrent -> str);
        }
    }
}

// place the intersection of src1 and src2 into dest
// This assumes the amount of items in src1 is greater than or equal to the amount of items in src2
void listset_intersect(struct listset * dest, struct listset * src1,
		       struct listset * src2) {
    struct listnode * srcCurrent = malloc(sizeof(struct listnode));
    for (srcCurrent = src1 -> head; srcCurrent != NULL; srcCurrent = srcCurrent -> next)
    {
        if (listset_lookup(src2, srcCurrent -> str) == 1)
        {
            listset_add(dest, srcCurrent -> str);
        }
    }
}

// return the number of items in the listset
int listset_cardinality(struct listset * this) {
    int count = 0;
    struct listnode * currentNode = malloc(sizeof(struct listnode));
    for (currentNode = this -> head; currentNode != NULL; currentNode = currentNode -> next)
    {
        count++;
    }
    return count;
}

// print the elements of the list set
void listset_print(struct listset * this) {
  struct listnode * p;

  for ( p = this->head; p != NULL; p = p->next ) {
    printf("%s, ", p->str);
  }
  printf("\n");
}
