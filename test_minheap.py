import unittest
from minheap import MinHeap

class TestMinHeap(unittest.TestCase):
	""" 
	Testcase of MinHeap class.

	Usage: 
		Easiest way >>>nosetests
		Or >>>python -m unittest test_minheap
	"""

	def test_peek(self):
		item = {"id":1, "price":1.0}
		heap = MinHeap()
		heap.push(item)
		self.assertEqual(heap.peek(), item)

	def test_pop(self):
		item_0 = {"id":1, "price":1.0}
		item_1 = {"id":2, "price":2.0}
		item_2 = {"id":3, "price":.0}
		heap = MinHeap()
		heap.push(item_0)
		heap.push(item_1)
		heap.push(item_2)
		self.assertEqual(heap.pop(), item_2)
		self.assertEqual(heap.pop(), item_0)
		self.assertEqual(heap.pop(), item_1)

	def test_peek_empty_heap(self):
		heap = MinHeap()
		self.assertRaises(IndexError, heap.peek)

	def test_pop_empty_heap(self):
		heap = MinHeap()
		self.assertRaises(IndexError, heap.pop)
		

if __name__ == '__main__':
	unittest.main()
