import heapq
from random import random
import timeit

def test():
	heap = []
	for i in xrange(100000):
		heapq.heappush(heap, (random(), i))
	
	while 1:
		try:
			heapq.heappop(heap)
		except IndexError:
			break


t = timeit.Timer("benchmark_heapq.test()", "import benchmark_heapq")
print "Pure python function, ", t.timeit(1), "secends."
