#define C_DEBUG_MEMORY_C  /* Have to be defined before including debug_memory.h */

#include "debug_memory.h"

debug_node_t* create_node(Site* site) {
  debug_node_t* head = malloc(sizeof(debug_node_t));
  head->site = site;
  head->next = NULL;
  return head;
}

void add_node(Site* site) {
  debug_node_t* current;
  if (debug_root_node == NULL) {
    debug_root_node = create_node(site);
  } else {
    current = debug_root_node;
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = create_node(site);
  }
}

void remove_node(Site* site) {
  debug_node_t* tmp_node;
  debug_node_t* current;
  if (debug_root_node->site == site) {
    tmp_node = debug_root_node;
    debug_root_node = debug_root_node->next;
    free(tmp_node);
    return;
  }
  current = debug_root_node;
  while (current->next != NULL) {
    if (current->next->site == site) {
      tmp_node = current->next;
      current->next = tmp_node->next;
      free(tmp_node);
    }
  }
}

void print_node(debug_node_t* node) {
  printf("address : %p\n", node->site);
  printf("size    : %zu bytes\n", node->site->s.n);
  printf("file    : %s\n", node->site->s.file);
  printf("line    : %d\n", node->site->s.line);
  printf("----------------------------------------\n");
}

void print_list() {
  debug_node_t *current = debug_root_node;
  if (current == NULL) return;
  printf("=== Allocated Memory ===================\n");
  while (current != NULL) {
    print_node(current);
    current = current->next;
  }
  printf("Total   : %d bytes\n", total_allocated);
  printf("========================================\n");
}

void* debug_malloc(size_t n, char *file, int line) {
  char *rp;
  rp = (char*)malloc(sizeof(Site)+n);
  total_allocated += n;
  ((Site*)rp)->s.n = n;
  ((Site*)rp)->s.file = file;
  ((Site*)rp)->s.line = line;
  add_node((Site*)rp);
  return (void*)(rp + sizeof(Site));
}

void* debug_calloc(size_t c, size_t n, char *file, int line) {
  char *rp;
  rp = (char*)calloc(sizeof(Site)+n*c, sizeof(char));
  total_allocated += n*c;
  ((Site*)rp)->s.n = n*c;
  ((Site*)rp)->s.file = file;
  ((Site*)rp)->s.line = line;
  add_node((Site*)rp);
  return (void*)(rp + sizeof(Site));
}

void* debug_realloc(void *ptr, size_t n, char *file, int line) {
  char *rp;
  char *tmp;
  tmp = ((char*)ptr) - sizeof(Site);
  total_allocated -= ((Site*)tmp)->s.n;
  rp = (char*)realloc(tmp, sizeof(Site)+n);
  total_allocated += n;
  ((Site*)rp)->s.n = n;
  ((Site*)rp)->s.file = file;
  ((Site*)rp)->s.line = line;
  add_node((Site*)rp);
  return (void*)(rp + sizeof(Site));
}

void debug_free(void *p, char *file, int line) {
  char *rp;
  rp = ((char*)p) - sizeof(Site);
  total_allocated -= ((Site*)rp)->s.n;
  ((Site*)rp)->s.file = file;
  ((Site*)rp)->s.line = line;
  remove_node((Site*)rp);
  free(rp);
}
