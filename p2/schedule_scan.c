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

struct node* get_next_down(struct node *temp, int track){
    int min_dis = __INT_MAX__;
    int dis;
    struct node *next = NULL;
    while (temp != NULL)
    {
        if (temp->access->position < track)
        {
            dis = abs(temp->access->position -  track);
            if (min_dis > dis)
            {
                min_dis = dis;
                next = temp;
            }
        }
        temp = temp->next;
    }
    return next;
}

struct node* get_next_up(struct node *temp, int track){
    int min_dis = __INT_MAX__;
    int dis;
    struct node *next = NULL;
    while (temp != NULL)
    {
        if (temp->access->position > track)
        {
            dis = abs(temp->access->position -  track);
            if (min_dis > dis)
            {
                min_dis = dis;
                next = temp;
            }
        }
        temp = temp->next;
    }
    return next;
}

void schedule()
{
    struct node *temp;
    struct access *t;
    struct node *temp2;
    temp = head;
    int n = 0;
    int track = 100;
    int total_tracks_traverse = 0;
    float avg_seek_length_time = 0;
    int trav;
    int up = 0;
    while (temp != NULL)
    {
        if (up)
            temp2 = get_next_up(temp, track);
        else
            temp2 = get_next_down(temp, track);
        if (temp2 == NULL)
        {
            up = abs(up - 1);
            temp = head;
        }
        else
        {
            trav = abs(track - temp2->access->position);
            run(temp2->access, trav);
            total_tracks_traverse += trav;
            track = temp2->access->position;
            n++;
            t = temp2->access;
            temp = head;
            delete (&head, t);
        }
    }

    avg_seek_length_time = (float)total_tracks_traverse / n;
    printf("Average seek length: %f\n", avg_seek_length_time);
}