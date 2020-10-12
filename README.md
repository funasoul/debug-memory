# debug-memory
Simple solution to debug malloc() and free(). I know that I can use valgrind etc.
for checking memory leak, but when I want to check memory leak on language bindings,
it's not so easy. I decided to write this code so that I can easily embed the memory
check in my C code.

[![Run on Repl.it](https://repl.it/badge/github/funasoul/debug-memory)](https://repl.it/github/funasoul/debug-memory)

## Introduction
Thanks to the document by
[Oracle](https://docs.oracle.com/javase/jp/8/docs/technotes/guides/troubleshoot/memleaks005.html#CIHDEEHJ),
I started to write this code from the above URL. Starting my implementation from the code by Oracle, I've
added `debug_calloc()`, `debug_realloc()` and several functions to print out leaked memory.

## Quickstart

```sh
% git clone https://github.com/funasoul/debug-memory.git
% cd debug-memory
% make run
./memtest
=== Allocated Memory ===================
address : 0x7f99e5f025c0
size    : 100 bytes
file    : test.c
line    : 10
----------------------------------------
address : 0x7f99e5f02650
size    : 6 bytes
file    : test.c
line    : 11
----------------------------------------
address : 0x7f99e5f02680
size    : 40 bytes
file    : test.c
line    : 12
----------------------------------------
address : 0x7f99e5f026d0
size    : 50 bytes
file    : test.c
line    : 13
----------------------------------------
Total   : 196 bytes
========================================

Checking for memory leak
=== Allocated Memory ===================
address : 0x7f99e5f02650
size    : 6 bytes
file    : test.c
line    : 11
----------------------------------------
address : 0x7f99e5f02680
size    : 40 bytes
file    : test.c
line    : 12
----------------------------------------
Total   : 46 bytes
========================================
```

## How to integrate with your code
Super easy. Just include `debug_memory.h`, and then call
`print_allocated_memory()` anywhere in your C code. Here is an example (just as same as
`test.c` in the repository).

```cpp
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
```

## Todo
- [x] Implement a wrapper for `strdup()` (will be done quite soon).
- [x] Change the name of the function `print_list()` to avoid name conflict.
