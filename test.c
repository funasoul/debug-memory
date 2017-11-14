/*
 * Author: Akira Funahashi <funa@bio.keio.ac.jp>
 * Last modified: Tue, 14 Nov 2017 18:37:44 +0900
 */
#include <stdio.h>
#include "debug_memory.h"

int main(int argc, char const* argv[])
{
  char* p = (char*)malloc(sizeof(char) * 100);
  char* q = (char*)malloc(sizeof(char) * 50);
  char* r = (char*)calloc(sizeof(int), 10);

  /* Print allocated memory */
  print_allocated_memory();

  free(p);
  q = NULL; /* memory leak! */
  free(r);

  /* Print allocated memory again */
  printf("\nChecking for memory leak\n");
  print_allocated_memory();

  return 0;
}
