# the pxd files in cython work like the header files - they
# contain declaration which are only included by cython modules.
# In addition, if the cython needs to call functions from the C libraries,
# pxd files are the best place to include the C headers, and import
# the function or type declarations.

# in order to use the uint32_t integer type, just import from the
# libc.stdint pxd file, which is already declared by cython.
# NOTE THAT if uint32_t is not imported explicitely, then the first parameter
# in the following function minheap_create(uint32_t, ...) would be regarded as
# a normal python parameter, but not a parameter with uint32_t type.
from libc.stdint cimport uint32_t

# when import a custom header file, remember to add a 'extern' keyword.
# And it's OK just to declare the struct name, but omit the details of
# struct itself, because cython does NOT care that.
cdef extern from "minheap.h":
    ctypedef struct minheap_t:
        pass

    # Just copy the function or function pointer's declarations as specified
    # in the C header file.
    ctypedef int (*compare)(void *, void *)
    ctypedef void *(*copy)(void *, void *)
    ctypedef void (*swap)(void *, void *)
    minheap_t *minheap_create(uint32_t, size_t, compare, copy, swap)
    void    minheap_free(minheap_t*)
    int     minheap_push(minheap_t*, void *)
    void    *minheap_pop(minheap_t*)
    void    *minheap_min(minheap_t*)

