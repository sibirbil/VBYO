#export THEANO_FLAGS="contexts=dev0->cuda0;dev1->cuda1"; python multi_16.py 

import numpy
import theano
import time

N = 16 * 1024;

v01 = theano.shared(numpy.random.random((N, N)).astype('float32'),
                    target='dev0')
v02 = theano.shared(numpy.random.random((N, N)).astype('float32'),
                    target='dev0')
v11 = theano.shared(numpy.random.random((N, N)).astype('float32'),
                    target='dev1')
v12 = theano.shared(numpy.random.random((N, N)).astype('float32'),
                    target='dev1')

f = theano.function([], [theano.tensor.dot(v01, v02),
                         theano.tensor.dot(v11, v12)])

t = time.time() 
f();
print "completed in %f seconds" %(time.time() - t)
