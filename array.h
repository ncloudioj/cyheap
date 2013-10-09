#ifndef _ARRAY_H_H
#define _ARRAY_H_H

#include <stdlib.h>
#include <stdint.h>

typedef struct {
    uint32_t    nelm;        /* current # of elements in array   */
    uint32_t    nrest;       /* rest # of elements in array      */
    size_t      size;        /* size of each item in array       */
    void        *elm;        /* point to the first item in array */
} array_t;


array_t * array_create(uint32_t n, size_t s);
void array_free(array_t *array);
void * array_push(array_t * array);
void * array_push_n(array_t * array, uint32_t n);
uint32_t array_len(array_t * array);
void * array_at(array_t * array, int index);

#endif
