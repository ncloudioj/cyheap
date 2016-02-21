#include "array.h"
#include "minheap.h"

#include <stdlib.h>


static void shiftdown(minheap_t *heap, int start, int at);
static void heapify(minheap_t *heap, int start);
static void shiftup(minheap_t *heap, int start);

struct minheap_t *
minheap_create(uint32_t n, size_t size, compare pfcmp, copy pfcpy, swap pfswp) {
    minheap_t *heap;

    heap = malloc(sizeof(minheap_t));
    if (heap == NULL) return NULL;
    heap->comp = pfcmp;
    heap->cpy = pfcpy;
    heap->swp = pfswp;
    heap->len = 0;
    heap->array = array_create(n, size);
    if (heap->array == NULL) {
		free(heap);
		return NULL;
    }
    return heap;
}

void
minheap_free(minheap_t *heap) {
    array_free(heap->array);
    free(heap);
}

int    
minheap_push(minheap_t *heap, const void *new) {
    void *item;

    if (heap->len == array_len(heap->array)) {
        if ((item=array_push(heap->array)) == NULL) {
            return -1;
        }
    } else {
        item = array_at(heap->array, heap->len);
    }

    heap->cpy(item, new);
    heap->len++;
    shiftdown(heap, 0, heap->len - 1);
    return 0;
}

void *
minheap_pop(minheap_t *heap) {
    void * root;
    
    if (heap->len == 0) return NULL;
    
    heap->swp(array_at(heap->array, 0), array_at(heap->array, heap->len-1));
    heap->len--;
    shiftup(heap, 0);
    root = array_at(heap->array, heap->len); /* note the previous first elm has been swapped to here. */
    return root;
}

void *
minheap_min(minheap_t *heap) {
    if (heap->len == 0) return NULL;
    return array_at(heap->array, 0);
}

static void
shiftdown(minheap_t *heap, int start, int end) {
    void *child, *parent;
    int i;  // index for the parent

    i = end;
    while (end > start) {
        child = array_at(heap->array, i);
        i = (end - 1) >> 1;
        parent = array_at(heap->array, i);
        if (heap->comp(child, parent) < 0) {
            heap->swp(child, parent);
            end = i;
        } else
            break;
    }

    return;
}

static void
shiftup(minheap_t *heap, int start) {
    int iend, istart, ichild, iright;

    iend = (int)heap->len;
    istart = start;
    ichild = 2 * istart + 1;
    while (ichild < iend) {
        iright = ichild + 1;
        if (iright < iend && heap->comp(array_at(heap->array, ichild),
                    array_at(heap->array, iright)) > 0) {
            ichild = iright;
        }
        heap->swp(array_at(heap->array, istart), array_at(heap->array, ichild));
        istart = ichild;
        ichild = 2 * istart + 1;
    }
    shiftdown(heap, start, istart);
    return;
}

static void
heapify(minheap_t *heap, int start) {
    int i;

    i = (int)(heap->len >> 2);
    for (; i >=0; i--) {
        shiftup(heap, i);
    }
    return;
}
