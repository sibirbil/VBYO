import theano
import theano.tensor as T
import numpy as np

r = T.row()
print r.broadcastable
#(True, False)

mtr = T.matrix()
print mtr.broadcastable
#(False, False)

f_row = theano.function([r, mtr], [r + mtr])

R = np.arange(3).reshape(1, 3)
print R
#array([[0, 1, 2]])
              
M = np.arange(9).reshape(3, 3)
print M
#array([[0, 1, 2],
#       [3, 4, 5],
#       [6, 7, 8]])
       
print f_row(R, M)
#[array([[  0.,   2.,   4.],
#       [  3.,   5.,   7.],
#       [  6.,   8.,  10.]])]

c = T.col()
print c.broadcastable
#(False, True)

f_col = theano.function([c, mtr], [c + mtr])
C = np.arange(3).reshape(3, 1)
print C
#array([[0],
#       [1],
#       [2]])

M = np.arange(9).reshape(3, 3)
print f_col(C, M)
#[array([[  0.,   1.,   2.],
#       [  4.,   5.,   6.],
#       [  8.,   9.,  10.]])]
