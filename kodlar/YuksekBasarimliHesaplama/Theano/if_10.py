from theano import tensor as T
from theano.ifelse import ifelse
import theano, time, numpy

a,b = T.scalars('a', 'b')
x,y = T.matrices('x', 'y')

#both ops build a condition over symbolic variables.

#ifElse takes a boolean condition and two variables as inputs.
z_lazy = ifelse(T.lt(a, b), T.mean(x), T.mean(y))

#switch takes a tensor as condition and two variables as inputs. switch is an elementwise operation and is thus more general than ifelse.
z_switch = T.switch(T.lt(a, b), T.mean(x), T.mean(y))

#whereas switch evaluates both output variables, ifelse is lazy and only evaluates one variable with respect to the condition.

#creating functions
f_switch = theano.function([a, b, x, y], z_switch,
                           mode=theano.Mode(linker='vm'))
f_lazyifelse = theano.function([a, b, x, y], z_lazy,
                               mode=theano.Mode(linker='vm'))

#these are values
val1 = 0.
val2 = 1.
big_mat1 = numpy.ones((10000, 1000))
big_mat2 = numpy.ones((10000, 1000))

n_times = 10

tic = time.time()
for i in range(n_times):
    f_switch(val1, val2, big_mat1, big_mat2)
print('time spent evaluating both values %f sec' % (time.time() - tic))

tic = time.time()
for i in range(n_times):
    f_lazyifelse(val1, val2, big_mat1, big_mat2)
print('time spent evaluating one value %f sec' % (time.time() - tic))
