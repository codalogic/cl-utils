cl-utils
========

cl-utils is a set of utilities that are helpful when coding, but
really too small to justify their own project.

The library will be added to over time as needs arise.

ptr_vector
----------

`ptr_vector` is a container that stores a vector of pointers.  The benefits
using it over `vector<T*>` is that it will deep-copy, the iterators return
`T&` rather than `T*`, and it will delete the pointed to objects when the
container is destroyed.  The benefits over `deque<T>` are that you can
`push_back()` an independently new-ed object, rather than having to do a copy
into place operation.
