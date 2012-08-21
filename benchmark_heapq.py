import heapq

def test():
	from numpy import random
	heap = []
	for i in xrange(100000):
		heapq.heappush(heap, (random.randn(), i))
	
	while 1:
		try:
			heapq.heappop(heap)
		except IndexError:
			break


import timeit
t = timeit.Timer("benchmark_heapq.test()", "import benchmark_heapq")
print "Pure python function, ", t.timeit(1), "secends."
