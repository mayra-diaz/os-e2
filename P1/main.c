#include "cma.h"
#include <stdio.h>
#include "test.h"

int main() {   
  printf("\nFirst fit \n");
  test_first_fit();

  printf("\nBest fit\n");
  test_best_fit();

  printf("\nWorst fit\n");
  test_worst_fit();

  printf("\nManual testing\n");
  test_manual_testing();
  return 0;
}