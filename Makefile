# Makefile of libminheap.so
#

CC = gcc
CFLAGS = -Wall -O2
OBJS = array.o minheap.o

all: libminheap

libminheap:$(OBJS)
	$(CC) -shared -fPIC $(CFLAGS) -Wl,-soname,libminheap.so.1 -o libminheap.so.1.0.0 $(OBJS)

test_heap:$(OBJS) test_heap.o
	$(CC) -o $@ $(CFLAGS) test_heap.c $(OBJS)

test_array:$(OBJS) test_array.o
	$(CC) -o $@ $(CFLAGS) test_array.c $(OBJS)

%.o:%.c
	$(CC) -c $(CFLAGS) $<

install: libminheap.so.1.0.0
	cp $< /usr/lib
	ldconfig
	ln -sf /usr/lib/libminheap.so.1 /usr/lib/libminheap.so

.PHONY:clean
clean:
	rm -f *.o libminheap.so.1.0.0 test_array test_heap
