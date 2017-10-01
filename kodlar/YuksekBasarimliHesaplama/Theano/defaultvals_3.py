from theano import In
from theano import tensor as T
from theano import function
x, y = T.dscalars('x', 'y')
z = x + y
f = function([x, In(y, value=1)], z)
print f(33)
print f(33, 2)
print '-' * 40

x, y, w = T.dscalars('x', 'y', 'w')
z = (x + y) * w
f = function([x, In(y, value=1), In(w, value=2, name='w_by_name')], z)
print f(33)
print f(33, 2)
print f(33, 0, 1)
print f(33, w_by_name=1)
print f(33, w_by_name=1, y=0)

#'In' does not know the name of the local variables y and w that are passed as arguments.
#The symbolic variable objects have name attributes (set by dscalars in the example above)
#and these are the names of the keyword parameters in the functions that we build.
#This is the mechanism at work in In(y, value=1). In the case of In(w, value=2, name='w_by_name').
#We override the symbolic variable’s name attribute with a name to be used for this function.
