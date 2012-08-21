import minheap
from random import random
import timeit

def test():
	heap = minheap.MinHeap()
	for i in xrange(100000):
		heap.push({"id":i, "price":random()})
	
	while 1:
		try:
			heap.pop()
		except IndexError:
			break


t = timeit.Timer("benchmark_minheap.test()", "import benchmark_minheap")
print "Cython extension completed in, ", t.timeit(1), "secends."
