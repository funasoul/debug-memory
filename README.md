# debug-memory
Simple solution to debug malloc() and free(). I know that I can use valgrind etc.
for checking memory leak, but when I want to check memory leak on language bindings,
it's not so easy. I decided to write this code so that I can easily embed the memory
check in my C code.

## Introduction
Thanks for the document by
[Oracle](https://docs.oracle.com/javase/jp/8/docs/technotes/guides/troubleshoot/memleaks005.html#CIHDEEHJ),
I started to write this code from the above URL. Starting my implementation from the code by Oracle, I've
added `debug_calloc()`, `debug_realloc()` and several functions to print out leaked memory.

## Quickstart

```sh
% git clone https://github.com/funasoul/debug-memory.git
% cd debug-memory
% make
% ./memtest
```

## How to integrate with your code
Super easy. Just include `debug_memory.h`, and then call
`print_list()` anywhere in your C code. Here is an example (just as same as
`test.c` in the repository).

```cpp
#include <stdio.h>
#include "debug_memory.h"

int main(int argc, char const* argv[])
{
  char* p = (char*)malloc(sizeof(char) * 100);
  char* q = (char*)malloc(sizeof(char) * 50);
  char* r = (char*)calloc(sizeof(int), 10);

  /* Print allocated memory */
  print_list();

  free(p);
  q = NULL; /* memory leak! */
  free(r);

  /* Print allocated memory again */
  printf("\nChecking for memory leak\n");
  print_list();

  return 0;
}
```

## Todo
- [] Implement a wrapper for `strdup()` (will be done quite soon).
