/*
 * Author: Akira Funahashi <funa@bio.keio.ac.jp>
 * Last modified: Tue, 14 Nov 2017 20:05:33 +0900
 */
#include <stdio.h>
#include "debug_memory.h"

int main(int argc, char const* argv[])
{
  char* p = (char*)malloc(sizeof(char) * 100);
  char* q = strdup("Hello");
  char* r = (char*)calloc(sizeof(int), 10);
  char* s = (char*)malloc(sizeof(char) * 50);

  /* Print allocated memory */
  print_allocated_memory();

  /* q and r will cause memory leak! */
  free(p);
  free(s);

  /* Print allocated memory again */
  printf("\nChecking for memory leak\n");
  print_allocated_memory();

  return 0;
}
