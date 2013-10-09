#include <assert.h>
#include <stdlib.h>
#include "array.h"

#define ARRAY_OK    0
#define ARRAY_ERROR 1

#define ARRAY_MEM_ERROR do {                    \
        exit(ARRAY_ERROR);                      \
    } while (0)


array_t *
array_create(uint32_t n, size_t s){
    array_t *a;
    uint32_t initial_number; /* initial number of elements in array, 1 by default */
    
    a = (array_t *)malloc(sizeof(array_t));
    if (a == NULL) {
        ARRAY_MEM_ERROR;
    }

    initial_number = n==0 ? 1 : n;
    a->elm = malloc(initial_number * s);
    if (a->elm == NULL) {
        ARRAY_MEM_ERROR;
    }
    a->nelm = 0;
    a->nrest = initial_number;
    a->size = s;

    return a;
}

void
array_free(array_t *array) {
    if(array->elm != NULL) {
        free(array->elm);
    }
    free(array);
}

void *
array_push(array_t * array) {
    void *ret, *elm;

    if (array->nrest > 0) {
        ret = (char *)array->elm + array->size*array->nelm;
        array->nrest--;
        array->nelm++;
        return ret;
    }

    /* double array's size, if failed, return NULL */
    if ((elm=realloc(array->elm, 2*array->size*array->nelm)) == NULL) {
        ARRAY_MEM_ERROR;
    } else {
        array->elm = elm;
        ret = (char *)array->elm + array->size * array->nelm;
        array->nrest = array->nelm - 1;
        array->nelm++;
    }

    return ret;
}

void *
array_push_n(array_t * array, uint32_t n) {
    void *ret, *elm;

    if (n == 0) return NULL;

    if (array->nrest >= n) {
        ret = (char *)array->elm + array->size*array->nelm;
        array->nrest -= n;
        array->nelm += n;
        return ret;
    }

    /* expand array's size, if failed, return NULL */
    size_t nslots;
    nslots = (2*array->nelm > n)? 2*array->nelm : array->nelm+array->nrest+n;
    if ((elm=realloc(array->elm, nslots*array->size)) == NULL) {
        ARRAY_MEM_ERROR;
    } else {
        array->elm = elm;
        ret = (char *)array->elm + array->size*array->nelm;
        array->nelm += n;
        array->nrest = nslots - array->nelm;
    }
    
    return ret;
}

uint32_t
array_len(array_t * array) {
    return array->nelm;
}

void *
array_at(array_t * array, int index) {
    assert(index >= 0);
    if (array->nelm > (uint32_t)index) {
        return (char *)array->elm + array->size*index;
    } else {
        return NULL;
    }
}
