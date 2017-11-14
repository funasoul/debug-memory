#ifndef H_DEBUG_MEMORY_H
#define H_DEBUG_MEMORY_H

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define DEBUG_MEMORY_DOTTED_VERSION "0.0.1"
#define DEBUG_MEMORY_VERSION 00001
#define DEBUG_MEMORY_VERSION_STRING "00001"

/* Total bytes allocated */
int total_allocated;

/* Memory alignment is important */
typedef union { double d; struct {size_t n; char *file; int line;} s; } Site;

/* linked list */
typedef struct debug_node {Site* site; struct debug_node* next; } debug_node_t;
debug_node_t* debug_root_node;

/* wrapper for malloc, free */
void* debug_malloc(size_t, char*, int);
void* debug_calloc(size_t, size_t, char*, int);
void* debug_realloc(void*, size_t, char*, int);
void debug_free(void*, char*, int);
char* debug_strdup(const char*, char*, int);
char* debug_strndup(const char*, size_t, char*, int);

/* util */
debug_node_t* create_node(Site*);
void add_node(Site*);
void remove_node(Site*);
void print_debug_node(debug_node_t*);
void print_allocated_memory(void);

/* debug_memory.c will not read this to avoid recursive expansion */
#ifndef C_DEBUG_MEMORY_C
#define malloc(n) debug_malloc(n, __FILE__, __LINE__)
#define calloc(c, n) debug_calloc(c, n, __FILE__, __LINE__)
#define realloc(p,n) debug_realloc(p, n, __FILE__, __LINE__)
#define free(p) debug_free(p, __FILE__, __LINE__)
#define strdup(p) debug_strdup(p, __FILE__, __LINE__)
#endif /* C_DEBUG_MEMORY_C */

#endif /* H_DEBUG_MEMORY_H */
