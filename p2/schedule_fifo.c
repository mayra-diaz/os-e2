#include "schedulers.h"
#include "cpu.h"
#include "list.h"
#include "access.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct node *head;
int id = 0;

void add(int position)
{
    struct access *current_access = malloc(sizeof(struct access));
    current_access->id = id;
    __atomic_fetch_add(&id, 1, __ATOMIC_SEQ_CST);
    current_access->position = position;
    insert(&head, current_access);
}

void schedule()
{
    struct node *temp;
    struct access *t;
    temp = head;
    int n = 0;
    int track = 100;
    int traverse;
    int total_tracks_traverse = 0;
    float avg_seek_length_time = 0;

    while (temp != NULL)
    {
        traverse = abs(track - temp->access->position);
        run(temp->access, traverse);
        total_tracks_traverse += traverse;
        track = temp->access->position;
        n++;
        t = temp->access;
        temp = temp->next;
        delete (&head, t);
    }
    avg_seek_length_time = (float)total_tracks_traverse / n;
    printf("Average seek length: %f\n", avg_seek_length_time);
}