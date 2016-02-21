#ifndef _ARRAY_H
#define _ARRAY_H

#include <stddef.h>
#include <stdint.h>

typedef struct array_t {
    uint32_t    nelm;        /* current # of elements in array   */
    uint32_t    nrest;       /* rest # of elements in array      */
    size_t      size;        /* size of each item in array       */
    void        *elm;        /* point to the first item in array */
} array_t;

#define ARRAY_AT(a, i) ((void *)(((char *)(a)->elm + (a)->size*(i))))
#define ARRAY_LEN(a) ((a)->nelm)

array_t * array_create(uint32_t n, size_t s);
void array_free(array_t *array);
void * array_push(array_t * array);
void * array_push_n(array_t * array, uint32_t n);
uint32_t array_len(array_t * array);
void * array_at(array_t * array, int i);

#endif
