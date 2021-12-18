#include "cma.h"
#include "list.h"
#include "debug.h"
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_bytes 1048576

void allocate_hole(struct list* holes, int begin, int end) {
  struct list_elem* f_hole = (struct list_elem *)malloc(sizeof(struct list_elem));
  f_hole->id = 0;
  f_hole->begin = begin;
  f_hole->type = 'H';
  f_hole->end = end;
  list_push_front(holes, f_hole);
}


void init_cma(struct list* processes, struct list* holes){
  list_init(processes);
  list_init(holes);
  allocate_hole(holes, 0, MAX_bytes);
}
// First fit. Allocate the first hole that is big enough. 
struct list_elem* first_fit(int n_bytes, struct list* holes){
  struct list_elem *current_hole = list_begin(holes);
  while (current_hole != list_end(holes)){
    int hole_size = current_hole->end - current_hole->begin;
    if (hole_size >= n_bytes){
      break; // We can stop searching as soon as we find a free hole that is large enough.
    }
    current_hole = list_next(current_hole);
  }
  return current_hole;
}

// Best fi . Allocate the smallest hole that is big enough.
struct list_elem* best_fit(int n_bytes, struct list* holes){
  struct list_elem *current_hole = list_begin(holes);
  struct list_elem *appropriate_hole = NULL;
  int min_space = MAX_bytes;
  while (current_hole != list_end(holes)){
    int hole_size = current_hole->end - current_hole->begin;
    if (hole_size >= n_bytes && min_space >= hole_size){
      min_space = hole_size; // We must search the entire list, unless the list is ordered by size.
      appropriate_hole = current_hole;
    }
    current_hole = list_next(current_hole);
  }
  return appropriate_hole;
}

// Worst fit. Allocate the largest hole. 
struct list_elem* worst_fit(int n_bytes, struct list* holes){
  struct list_elem *current_hole = list_begin(holes);
  struct list_elem *appropriate_hole = NULL;
  int bigger_space = n_bytes;
  while (current_hole != list_end(holes)){
    int hole_size = current_hole->end - current_hole->begin;
    if (hole_size >= n_bytes && hole_size >= bigger_space){
      appropriate_hole = current_hole; // Again, we must search the entire list, unless it is sorted by size
      bigger_space = hole_size;
    }
    current_hole = list_next(current_hole);
  }
  return appropriate_hole;
}

// Request for a contiguous block of memory
bool request(int n_bytes, char type, int id, struct list* processes, struct list* holes){
  struct list_elem *new_procces = (struct list_elem *)malloc(sizeof(struct list_elem));
  new_procces->type = 'P';
  new_procces->id = id;
  // If there is sufficient space
  if(list_size(holes) > 1){
    struct list_elem* current_hole = NULL;
    // choice of the strategy to be followed
    if(type == 'F'){
        current_hole = first_fit(n_bytes, holes);
    }else if(type == 'B'){
        current_hole = best_fit(n_bytes, holes);
    }else if(type == 'W'){
        current_hole = worst_fit(n_bytes, holes);
    }
    // If there is sufficient space
    if(current_hole != list_end(holes)){
      // Hardware address protection with base and limit registers
      new_procces->begin = current_hole->begin;
      new_procces->end = new_procces->begin + n_bytes;
      // Hole left over
      current_hole->begin = new_procces->end;
      int left_over = current_hole->end - current_hole->begin;
      if (left_over == 0){ list_remove(current_hole);}
      list_insert_ordered(processes, new_procces, sort_by_begin, NULL);
    }else{
        printf("Insufficient space for %d\n", n_bytes);
        return false;
        } 
  }else{
    struct list_elem* last_hole = list_back(holes);
    // If there isn't sufficient space
    if(n_bytes > last_hole->end){
      printf("Insufficient space for %d bytes. \n", n_bytes);
      return false;
    }
    if(list_empty(processes)){
      new_procces->begin = 0;
      new_procces->end = n_bytes;
      list_push_back(processes, new_procces);
    // If there is sufficient space
    }else{
      struct list_elem *last_elem = list_back(processes);
      new_procces->begin = last_elem->end;
      new_procces->end = new_procces->begin + n_bytes;
      list_push_back(processes, new_procces);
    }
    last_hole->begin += n_bytes;
  }
  return true;
}

// Compact unused holes of memory into one single block
// Memory will be relocated so that the processes are at one end and the holes at the other end
void compact(struct list *processes, struct list *holes){
  struct list_elem *current_procces = NULL;
  int last_begin = 0;
  for (current_procces = list_begin(processes); current_procces != list_end(processes); current_procces = list_next(current_procces)){
    if (last_begin == 0){
      current_procces->end = current_procces->end - current_procces->begin;
      current_procces->begin = 0;
      last_begin = current_procces->end;
    }else{
      int n_bytes = current_procces->end - current_procces->begin;
      current_procces->begin = last_begin;
      current_procces->end = current_procces->begin + n_bytes;
      last_begin = current_procces->end;
    }
  }
  while (!list_empty(holes)){
    struct list_elem *current_hole = list_begin(holes);
    list_pop_front(holes);
    free(current_hole);
  }
  allocate_hole(holes, last_begin, MAX_bytes);
}

// Release of a contiguous block of memory
bool release(int id, struct list *processes, struct list *holes){
  struct list_elem *e = NULL;
  // We look for the id corresponding to the process to be released
  for (e = list_begin(processes); e != list_end(processes); e = list_next(e)){
    if (e->id == id){break;}
  }
  // If the process does not exist
  if (e == list_end(processes)) return false;
  // We release the memory
  struct list_elem* free_space = e;
  list_remove(e);
  free_space->type = 'H';
  // We add the new hole to the list of holes
  list_insert_ordered(holes, free_space, sort_by_begin, NULL);
  return true;
}

void status_report(struct list *processes, struct list *holes){
  if(list_empty(processes)){
    struct list_elem *last_hole = list_back(holes);
    printf("Addresses [%d:%d] Unused\n", last_hole->begin, last_hole->end);
    return;
  }
  struct list_elem *current_procces = list_begin(processes);
  struct list_elem *current_hole = list_begin(holes);
  while(current_procces!=list_end(processes) && current_hole!=list_end(holes)){
    if(current_procces->begin < current_hole->begin){
      printf("Addresses [%d:%d] Process P%d\n", current_procces->begin, current_procces->end, current_procces->id);
      current_procces = list_next(current_procces);
    }else{
      printf("Addresses [%d:%d] Unused\n", current_hole->begin, current_hole->end);
      current_hole = list_next(current_hole);
    }
  }
  while(current_procces != list_end(processes)){  
    printf("Addresses [%d:%d] Process P%d\n", current_procces->begin + 1, current_procces->end, current_procces->id);
    current_procces = list_next(current_procces);
  }
  
  while(current_hole!=list_end(holes)){
    printf("Addresses [%d:%d] Unused\n", current_hole->begin, current_hole->end);
    current_hole = list_next(current_hole);
  }
}

void destructor_cma(struct list *processes, struct list *holes){
  while(!list_empty(processes)){
    struct list_elem *current_procces = list_begin(processes);
    list_pop_front(processes);
    free(current_procces);
  }
  while (!list_empty(holes)){
    struct list_elem *current_hole = list_begin(holes);
    list_pop_front(holes);
    free(current_hole);
    }
}

bool sort_by_begin(const struct list_elem *a,const struct list_elem *b, void *aux UNUSED){
  return a->begin < b->begin;
}