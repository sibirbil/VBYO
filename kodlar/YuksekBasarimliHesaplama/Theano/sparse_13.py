#Theano implements two formats of sparse matrix: csc and csr.
#Those are almost identical except that csc is based on the columns of the matrix and csr is based on its rows. 

#They both have the same purpose: to provide for the use of efficient algorithms performing linear algebra operations.
#A disadvantage is that they fail to give an efficient way to modify the sparsity structure of the underlying matrix, i.e. adding new elements.
#This means that if you are planning to add new elements in a sparse matrix very often in your computational graph, perhaps a tensor variable could be a better choice.

import theano
import numpy as np
import scipy.sparse as sp
from theano import sparse

# - The data attribute is a one-dimensional ndarray which contains all the non-zero elements of the sparse matrix.
# - The indices and indptr attributes are used to store the position of the data in the sparse matrix.
# - The shape attribute is exactly the same as the shape attribute of a dense (i.e. generic) matrix.
#   It can be explicitly specified at the creation of a sparse matrix if it cannot be infered from the first three attributes.

# converters are implemented
x = sparse.csc_matrix(name='x', dtype='float32')
y = sparse.dense_from_sparse(x)
z = sparse.csc_from_dense(y)

# the attribute arrays can be extracted and a sparse matrix can be created
data, indices, indptr, shape = sparse.csm_properties(x)
t = sparse.CSR(data, indices, indptr, shape)
f = theano.function([x], t)

a = sp.csc_matrix(np.asarray([[0, 1, 2], [0, 0, 0], [3, 0, 0]], dtype='float32'))
print(a.toarray())
print(f(a).toarray())

print '-' * 50

#Several ops are set to make use of the very peculiar structure of the sparse matrices.
#These ops are said to be structured and simply do not perform any computations on the zero elements of the sparse matrix.
u = sparse.structured_add(x, 2)
g = theano.function([x], u)
print(a.toarray())
print(g(a).toarray())
