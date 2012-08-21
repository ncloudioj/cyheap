from distutils.core import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext

ext_modules = [Extension("minheap", ["cyminheap.pyx"], 
				libraries=['minheap'])]

setup(
		name = "My minimal heap",
		cmdclass = {'build_ext': build_ext},
		ext_modules = ext_modules
	)
