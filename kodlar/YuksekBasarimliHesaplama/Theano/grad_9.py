import numpy
import theano
import theano.tensor as T
from theano import pp
x = T.dscalar('x')
y = 2 * (x ** 3);
gy = T.grad(y, x)

# print out the gradient prior to optimization
f = theano.function([x], gy)
print pp(f.maker.fgraph.outputs[0])

print f(4)

#The grad function works symbolically: it receives and returns Theano variables.
#grad can be compared to a macro since it can be applied repeatedly.
#Scalar costs only can be directly handled by grad. Arrays are handled through repeated applications.
