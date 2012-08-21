#!/usr/bin/env python

class miniheap:
	def __init__(self):
		self.data = []
		self.len = 0

	#def __init__(self, data):
	#	self.data = data
	#	self.len = len(self.data)
	#	for i in xrange(self.len/2,-1,-1):
	#		self.__heapify__(i)

	def min(self):
		return self.data[0];

	def insert(self, item):
		if self.len == len(self.data):
			self.data.append(item)
		else:
			self.data[self.len] = item
		self.len += 1
		smallest = self.len / 2
		self.__shiftup__(self.len-1, smallest)

	def __shiftup__(self, start, at):
		if self.data[start] < self.data[at]:
			self.data[at], self.data[start] = self.data[start], self.data[at]
			self.__shiftup__(at,at/2)

	def delete(self, item):
		pass

	def pop(self):
		if self.len == 0:
			raise StandardError("no item in the queue...")
		root = self.min()
		self.data[0] = self.data[self.len-1]
		self.len -= 1
		self.__heapify__(0)
		return root

	def __iter__(self):
		pass

	def __heapify__(self, start):
		if self.len <= 1:
			return
		left = 2*(start+1) - 1
		right = 2*(start+1)
		smallest = start
		if left <= (self.len-1) and self.data[left] < self.data[smallest]:
			smallest = left
		if right <= (self.len-1) and self.data[right] < self.data[smallest]:
			smallest = right
		if smallest != start:
			self.data[smallest], self.data[start] = self.data[start], self.data[smallest]
			self.__heapify__(smallest)

class Item(object):
	
	def __init__(self, id, price):
		self.id = id
		self.price = price

	def __lt__(self, other):
		return self.price < other.price

def test():
	from numpy import random
	heap = miniheap()
	for i in xrange(100000):
		heap.insert(Item(i, random.randn()))
	
	while 1:
		try:
			heap.pop()
		except StandardError:
			break


import timeit
t = timeit.Timer("miniheap.test()", "import miniheap")
print "Pure python function, ", t.timeit(1), "secends."
