from distutils.core import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext


ext_modules = [Extension("minheap",
                         ["cyminheap.pyx"],
                         libraries=['minheap'],
                         library_dirs=["/usr/local/lib"],
                         include_dirs=["/usr/local/include"],
                         runtime_library_dirs=["/usr/local/lib"])]

setup(
    name = "My minimal heap",
    cmdclass = {'build_ext': build_ext},
    ext_modules = ext_modules
)
