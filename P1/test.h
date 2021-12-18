#include "cma.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
void test_first_fit(){
  struct cma CMemAlloc;
  init_cma(&CMemAlloc.processes, &CMemAlloc.holes);
  printf("Request->RQ\n");
  request(80000, 'F', 1, &CMemAlloc.processes, &CMemAlloc.holes);
  request(50000, 'F', 2, &CMemAlloc.processes, &CMemAlloc.holes);
  request(90000, 'F', 3, &CMemAlloc.processes, &CMemAlloc.holes);
  request(80000, 'F', 4, &CMemAlloc.processes, &CMemAlloc.holes);
  request(40000, 'F', 5, &CMemAlloc.processes, &CMemAlloc.holes);
  request(60000, 'F', 6, &CMemAlloc.processes, &CMemAlloc.holes);
  request(15000, 'F', 7, &CMemAlloc.processes, &CMemAlloc.holes);
  request(100000, 'F', 8, &CMemAlloc.processes, &CMemAlloc.holes);
  request(65000, 'F', 9, &CMemAlloc.processes, &CMemAlloc.holes);
  request(78000, 'F', 10, &CMemAlloc.processes, &CMemAlloc.holes);

  status_report(&CMemAlloc.processes, &CMemAlloc.holes);

  printf("Release->RL\n");
  release(3, &CMemAlloc.processes, &CMemAlloc.holes);
  release(5, &CMemAlloc.processes, &CMemAlloc.holes);
  release(9, &CMemAlloc.processes, &CMemAlloc.holes);

  status_report(&CMemAlloc.processes, &CMemAlloc.holes);

  printf("Some more requests->RQ\n");
  request(67800, 'F', 11, &CMemAlloc.processes, &CMemAlloc.holes);
  request(35000, 'F', 12, &CMemAlloc.processes, &CMemAlloc.holes);
  
  status_report(&CMemAlloc.processes, &CMemAlloc.holes);
  
  printf("Compact->C\n");
  compact(&CMemAlloc.processes, &CMemAlloc.holes);
  
  status_report(&CMemAlloc.processes, &CMemAlloc.holes);
  
  destructor_cma(&CMemAlloc.processes, &CMemAlloc.holes);

}

void test_best_fit(){
  struct cma CMemAlloc;
  init_cma(&CMemAlloc.processes, &CMemAlloc.holes);
  printf("Request->RQ\n");
  request(80000, 'B', 1, &CMemAlloc.processes, &CMemAlloc.holes);
  request(50000, 'B', 2, &CMemAlloc.processes, &CMemAlloc.holes);
  request(90000, 'B', 3, &CMemAlloc.processes, &CMemAlloc.holes);
  request(80000, 'B', 4, &CMemAlloc.processes, &CMemAlloc.holes);
  request(40000, 'B', 5, &CMemAlloc.processes, &CMemAlloc.holes);
  request(60000, 'B', 6, &CMemAlloc.processes, &CMemAlloc.holes);
  request(15000, 'B', 7, &CMemAlloc.processes, &CMemAlloc.holes);
  request(100000, 'B', 8, &CMemAlloc.processes, &CMemAlloc.holes);
  request(65000, 'B', 9, &CMemAlloc.processes, &CMemAlloc.holes);
  request(78000, 'B', 10, &CMemAlloc.processes, &CMemAlloc.holes);
  
  status_report(&CMemAlloc.processes, &CMemAlloc.holes);
  
  printf("Release->RL\n");
  release(3, &CMemAlloc.processes, &CMemAlloc.holes);
  release(5, &CMemAlloc.processes, &CMemAlloc.holes);
  release(9, &CMemAlloc.processes, &CMemAlloc.holes);
  
  status_report(&CMemAlloc.processes, &CMemAlloc.holes);
  
  printf("Some more requests->RQ\n");
  request(67800, 'B', 11, &CMemAlloc.processes, &CMemAlloc.holes);
  request(35000, 'B', 12, &CMemAlloc.processes, &CMemAlloc.holes);
  
  status_report(&CMemAlloc.processes, &CMemAlloc.holes);
  
  printf("Compact->C\n");
  compact(&CMemAlloc.processes, &CMemAlloc.holes);
  
  status_report(&CMemAlloc.processes, &CMemAlloc.holes);
  
  destructor_cma(&CMemAlloc.processes, &CMemAlloc.holes);
}

void test_worst_fit(){
  struct cma CMemAlloc;
  init_cma(&CMemAlloc.processes, &CMemAlloc.holes);
  printf("Request->RQ\n");
  request(80000, 'W', 1, &CMemAlloc.processes, &CMemAlloc.holes);
  request(50000, 'W', 2, &CMemAlloc.processes, &CMemAlloc.holes);
  request(90000, 'W', 3, &CMemAlloc.processes, &CMemAlloc.holes);
  request(80000, 'W', 4, &CMemAlloc.processes, &CMemAlloc.holes);
  request(40000, 'W', 5, &CMemAlloc.processes, &CMemAlloc.holes);
  request(60000, 'W', 6, &CMemAlloc.processes, &CMemAlloc.holes);
  request(15000, 'W', 7, &CMemAlloc.processes, &CMemAlloc.holes);
  request(100000, 'W', 8, &CMemAlloc.processes, &CMemAlloc.holes);
  request(65000, 'W', 9, &CMemAlloc.processes, &CMemAlloc.holes);
  request(78000, 'W', 10, &CMemAlloc.processes, &CMemAlloc.holes);
  
  status_report(&CMemAlloc.processes, &CMemAlloc.holes);
  
  printf("Release->RL\n");
  release(3, &CMemAlloc.processes, &CMemAlloc.holes);
  release(5, &CMemAlloc.processes, &CMemAlloc.holes);
  release(9, &CMemAlloc.processes, &CMemAlloc.holes);
  
  status_report(&CMemAlloc.processes, &CMemAlloc.holes);
  
  printf("Some more requests->RQ\n");
  request(67800, 'W', 11, &CMemAlloc.processes, &CMemAlloc.holes);
  request(35000, 'W', 12, &CMemAlloc.processes, &CMemAlloc.holes);
  
  status_report(&CMemAlloc.processes, &CMemAlloc.holes);
  
  printf("Compact->C\n");
  compact(&CMemAlloc.processes, &CMemAlloc.holes);
  
  status_report(&CMemAlloc.processes, &CMemAlloc.holes);
  
  destructor_cma(&CMemAlloc.processes, &CMemAlloc.holes);
}

void test_manual_testing(){
  char entry[30];
  struct cma CMemAlloc;
  init_cma(&CMemAlloc.processes, &CMemAlloc.holes);
  while (true) {
    printf("\nallocator> ");
    fgets(entry, sizeof(entry), stdin);
    char *operation = strtok(entry, " ");
    if (strcmp(operation, "RQ") == 0) {
        printf("RQ\n");
        char *id = strtok(NULL, " ");
        char *char_space = strtok(NULL, " ");
        int space = atoi(char_space);
        request(space, *operation , atoi(id), &CMemAlloc.processes ,&CMemAlloc.holes);
    } else if (strcmp(operation, "RL") == 0) {
      printf("RL\n");
      char *id = strtok(NULL, " ");
      release(atoi(id), &CMemAlloc.processes ,&CMemAlloc.holes);
    } else if (strcmp(operation, "C") == 0) {
      printf("C\n");
      compact(&CMemAlloc.processes ,&CMemAlloc.holes);
    } else if (strcmp(operation, "STAT") == 0) {
      printf("STAT\n");
      status_report(&CMemAlloc.processes ,&CMemAlloc.holes);
    } else if (strcmp(operation, "X") == 0) {
        printf("X\n");
        exit(0);
    } else
      printf("No command specified\n");
  }
}