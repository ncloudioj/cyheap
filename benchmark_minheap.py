import minheap

def test():
	from numpy import random
	heap = minheap.MinHeap()
	for i in xrange(100000):
		heap.push({"id":i, "price":random.randn()})
	
	while 1:
		try:
			heap.pop()
		except IndexError:
			break


import timeit
t = timeit.Timer("benchmark.test()", "import benchmark")
print "Cython extension completed in, ", t.timeit(1), "secends."
