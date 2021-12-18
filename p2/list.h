/**
 * list data structure containing the tasks in the system
 */

#include "access.h"

struct node {
    Access *access;
    struct node *next;
};

// insert and delete operations.
void insert(struct node **head, Access *access);
void delete(struct node **head, Access *access);
void traverse(struct node *head);
