#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "array.h"
#include "minheap.h"

#define MINHEAP_OK		0
#define MINHEAP_ERROR 	1

#define MINHEAP_MEM_ERROR 					\
	do {									\
		perror("memory error in minheap");	\
		exit(MINHEAP_ERROR);				\
	} while(0)


static void shiftup(minheap_t *heap, int start, int at);
static void heapify(minheap_t *heap, int start);

minheap_t *
minheap_create(uint32_t n, size_t size, compare pfcmp, copy pfcpy, swap pfswp) {
	minheap_t *heap;

	heap = (minheap_t*)malloc(sizeof(minheap_t));
	if (heap == NULL) MINHEAP_MEM_ERROR;
	heap->comp = pfcmp;
	heap->cpy = pfcpy;
	heap->swp = pfswp;
	heap->len = 0;
	heap->array = array_create(n, size);
	if (heap->array == NULL) MINHEAP_MEM_ERROR;
	return heap;
}

void
minheap_free(minheap_t *heap) {
	array_free(heap->array);
	free(heap);
}

void	
minheap_push(minheap_t *heap, const void *new) {
	void *item;
	int smallest;

	if (heap->len == array_len(heap->array)) {
		if ((item=array_push(heap->array)) == NULL) {
			MINHEAP_MEM_ERROR;
		}
	} else {
		item = array_at(heap->array, heap->len);
	}

	heap->cpy(item, new);
	heap->len++;
	smallest = heap->len / 2;
	shiftup(heap, heap->len-1, smallest);
}

void *
minheap_pop(minheap_t *heap) {
	if (heap->len == 0) return NULL;

	void * root;
	
	heap->swp(array_at(heap->array, 0), array_at(heap->array, heap->len-1));
	heap->len--;
	heapify(heap, 0);
	root = array_at(heap->array, heap->len); /* note the previous first elm has been swapped to here. */
	return root;
}

void *
minheap_min(minheap_t *heap) {
	if (heap->len == 0) return NULL;
	return array_at(heap->array, 0);
}



static void
shiftup(minheap_t *heap, int start, int at) {
	void *bottom, *top;
	
	bottom = array_at(heap->array, start);
	top = array_at(heap->array, at);
	if (heap->comp(bottom, top) < 0) {
		heap->swp(bottom, top);	
		shiftup(heap, at, at/2);
	}
}

static void
heapify(minheap_t *heap, int start) {
	if (heap->len <= 1) return;

	int left, right, smallest;
	void *t, *tsmallest;

	left = 2*(start+1) - 1;
	right = left + 1;
	smallest = start;
	if (left <= heap->len-1) {
		tsmallest = array_at(heap->array, smallest);
		t = array_at(heap->array, left);
		if (heap->comp(tsmallest, t) > 0) {
			smallest = left;
		}
	}
	if (right <= heap->len-1) {
		tsmallest = array_at(heap->array, smallest);
		t = array_at(heap->array, right);
		if (heap->comp(tsmallest, t) > 0) {
			smallest = right;
		}
	}
	if (smallest != start) {
		heap->swp(array_at(heap->array, smallest), array_at(heap->array, start));
		heapify(heap, smallest);
	}
}
