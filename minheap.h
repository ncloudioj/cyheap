#ifndef _MIN_HEAP_H
#define _MIN_HEAP_H

#include "array.h"
#include <stdint.h>

typedef int (*compare)(const void *, const void *);
typedef void *(*copy)(void *, const void *);
typedef void (*swap)(void *, void *);

typedef struct minheap_t {
    uint32_t    len;        /* length of minheap, might be less than the actual size of array. */
    struct array_t     *array;     /* dynamic array for storing the elmentes of minheap */
    compare     comp;       /* cumstomized comparator */
    copy        cpy;        /* cumstomized copy operator */
    swap        swp;        /* cumstomized swap operator */
} minheap_t;

struct minheap_t *minheap_create(uint32_t, size_t, compare, copy, swap);
void minheap_free(minheap_t*);
int minheap_push(minheap_t*, const void *);
void *minheap_pop(minheap_t*);
void *minheap_min(minheap_t*);

#endif
