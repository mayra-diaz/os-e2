#ifndef __LIB_CMA_H
#define __LIB_CMA_H
/*cma->Contiguos Memory Allocation*/
#include "debug.h"
#include "list.h"
// You will need linked lists to represent the processes and holes within the menoria.
struct cma{
  struct list processes;
  struct list holes;
};

void allocate_hole(struct list* holes, int begin, int end);
void init_cma(struct list* processes, struct list* holes);

// Strategies for the dynamic storage allocation problem.
struct list_elem* first_fit(int n_bytes, struct list* holes);
struct list_elem* best_fit(int n_bytes, struct list* holes);
struct list_elem* worst_fit(int n_bytes, struct list* holes);
/*
Request required by the program
1. Request for a contiguous block of memory
2. Release of a contiguous block of memory
3. Compact unused holes of memory into one single block
4. Report the regions of free and allocated memory
*/
bool request(int n_bytes, char type, int id, struct list* processes, struct list* holes);
void compact(struct list *processes, struct list *holes);
bool release(int id, struct list *processes, struct list *holes);
void status_report(struct list *processes, struct list *holes);

void destructor_cma(struct list *processes, struct list *holes);

bool sort_by_begin(const struct list_elem *a,const struct list_elem *b, void *aux UNUSED);

#endif