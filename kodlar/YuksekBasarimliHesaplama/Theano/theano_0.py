import numpy
import theano.tensor as T
from theano import function
from theano import pp

#In Theano, all symbols must be typed.
#In particular, T.dscalar is the type we assign to 0-dimensional arrays (scalar) of doubles (d)
#It is a Theano Type.
x = T.dscalar('x') #try the same with matrix
y = T.dscalar('y')
print '-' * 50

#what is x: it is a TensorVariable
print 'type(x):', type(x)

#their type field is assigned to T.dscalar
print 'x.type:', x.type
print 'T.dscalar:', T.dscalar
print x.type is T.dscalar
print '-' * 50

#dscalar is not a class. Therefore, neither x nor y are actually instances of dscalar.
#They are instances of TensorVariable. x and y are, however, assigned the theano Type dscalar in their type field.

z = x + y #z is another variable that represents x+y
print 'z.type:', z.type
print 'x:', pp(x)
print 'y:', pp(y)
print 'z:', pp(z)
print '-' * 50

f = function([x, y], z) #or function([x, y], x + y)
print f
print '-' * 50

print f(2, 3)
print numpy.allclose(f(16.3, 12.1), 28.4) #allclose: teturns True if two arrays are element-wise equal within a tolerance.
print '-' * 50

#now try with matrices
x = T.dmatrix('x')
y = T.dmatrix('y')
z = x + y
f = function([x, y], z)
print f([[1, 2], [3, 4]], [[10, 20], [30, 40]])
print f(numpy.array([[1, 2], [3, 4]]), numpy.array([[10, 20], [30, 40]]))
print '-' * 50

#exercise:
a = T.vector() # declare variable
out = a + a ** 10  # build symbolic expression
f = function([a], out) # compile function
print(f([0, 1, 2]))

#Modify and execute this code to compute this expression: a ** 2 + b ** 2 + 2 * a * b.
#see solution_0.py for exercise

