#The way to think about putting randomness into Theanos computations is to put random variables in your graph.
#Theano will allocate a NumPy RandomStream object (a random number generator) for each such variable, and draw from it as necessary.
#We will call this sort of sequence of random numbers a random stream.
#Random streams are at their core shared variables, so the observations on shared variables hold here as well.
#Theanoss random objects are defined and implemented in RandomStreams and, at a lower level, in RandomStreamsBase.

import theano
from theano.tensor.shared_randomstreams import RandomStreams
from theano import function
srng = RandomStreams(seed=234)
rv_u = srng.uniform((2,2))
rv_n = srng.normal((2,2))
f = function([], rv_u)
g = function([], rv_n, no_default_updates=True)    #Not updating rv_n.rng
nearly_zeros = function([], rv_u + rv_u - 2 * rv_u) #The random variable drawn at most once in a single execution

f_val0 = f()
f_val1 = f()

g_val0 = g()
g_val1 = g()

print f_val0, f_val1
print '-' * 5
print g_val0, g_val1
print '-' * 5
print nearly_zeros()
print '-' * 5

#you can seed the rngs
rng_val = rv_u.rng.get_value(borrow=True)
rng_val.seed(89234)
rv_u.rng.set_value(rng_val, borrow=True)

srng.seed(902340) #another way to seed the rngs (with different seeds)  
