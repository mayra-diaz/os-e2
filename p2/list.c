/**
 * Various list operations
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list.h"
#include "access.h"


// add a new Access to the list of Accesss
void insert(struct node **head, Access *newAccess) {
    // add the new Access to the list 
    struct node *newNode = malloc(sizeof(struct node));

    newNode->access = newAccess;
    newNode->next = *head;
    *head = newNode;
}

// delete the selected Access from the list
void delete(struct node **head, Access *access) {
    struct node *temp;
    struct node *prev;

    temp = *head;
    // special case - beginning of list
    if (access->id == temp->access->id) {
        *head = (*head)->next;
    }
    else {
        // interior or last element in the list
        prev = *head;
        temp = temp->next;
        while (access->id != temp->access->id) {
            prev = temp;
            temp = temp->next;
        }

        prev->next = temp->next;
    }
}

// traverse the list
void traverse(struct node *head) {
    struct node *temp;
    temp = head;

    while (temp != NULL) {
        printf("[%d] [%d]\n",temp->access->id, temp->access->position);
        temp = temp->next;
    }
}
