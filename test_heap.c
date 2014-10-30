#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include "minheap.h"

typedef struct {
    int                 id;
    struct timeval      time;
} my_timer_t;

static inline void timer_swap(void *, void*);
static inline void *timer_copy(void *, const void*);
static inline int timer_cmp(const void*, const void*);
int id_cmp(const void*, const void*);

static inline void
timer_swap(void *p, void *q) {
    if (p == q) return;
    
    my_timer_t *l, *r;
    my_timer_t temp;

    l = (my_timer_t *)p;
    r = (my_timer_t *)q;
    temp = *l;
    *l = *r;
    *r = temp;
}

static inline void *
timer_copy(void *l, const void *r) {
    *(my_timer_t *)l = *(my_timer_t *)r;
    return l;
}

static inline int
timer_cmp(const void * l, const void * r) {
    const struct timeval *lt, *rt;
    
    lt = &(((const my_timer_t *)l)->time);
    rt = &(((const my_timer_t *)r)->time);

    if (lt->tv_sec == rt->tv_sec) {
        if (lt->tv_usec > rt->tv_usec) {
            return 1;
        } else if (lt->tv_usec == lt->tv_usec) {
            return 0;
        } else return -1;
    }
    else {
        if (lt->tv_sec > rt->tv_sec)    return 1;
        else return -1;
    }
}

int
id_cmp(const void *l, const void *r) {
    const my_timer_t * lt, *rt;

    lt = (const my_timer_t *) l;
    rt = (const my_timer_t *) r;

    if (lt->id > rt->id) return 1;
    else if (lt->id == rt->id) return 0;
    else return -1;
}

int
main(int argc, char **argv) {
    int i;
    int ntest, nfailure;
    struct timeval now;
    my_timer_t timer;
    minheap_t * heap;

    ntest = nfailure = 0;

    ntest++;
    heap = minheap_create(0, sizeof(my_timer_t), id_cmp, timer_copy, timer_swap );
    for(i=0; i<50000; i++) {
        gettimeofday(&now, NULL);
        timer.id = 60000-i;
        timer.time = now;
        //timer.time.tv_sec -= i;
        minheap_push(heap, &timer);
        fprintf(stdout,"push timer id:%d\n", timer.id);
        sleep(0);
    }

    my_timer_t * pop;
    while((pop=minheap_pop(heap)) != NULL){
        fprintf(stdout, "current timer id:%d\n", pop->id);
    }

    exit(0);
}
