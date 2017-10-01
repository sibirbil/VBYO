#use THEANO_FLAGS=device=cpu or device=cuda[0,1,2,3]
#device is the device you want to use
#cuda (or cuda0) is the gpu
#cuda1 is the second gpu if you have one

# try with the flag floatX=float32
# the same can be obtained by putting this inside the code: theano.config.floatX = 'float32'

# then try with the additional flag profile=True

import theano
from theano import function, config, shared, tensor
import numpy
import matplotlib.pyplot as plt
import time

rng = numpy.random

# training Data
vlen = 1024 * 1024 * 2
X = numpy.asarray(rng.rand(vlen), config.floatX)
Y = numpy.asarray(rng.rand(vlen), config.floatX)

m_value = rng.randn()
c_value = rng.randn()
m = theano.shared(m_value, name ='m')
c = theano.shared(c_value, name ='c')

x = theano.shared(X, name = 'x')
y = theano.shared(Y, name = 'y')
num_samples = X.shape[0]

prediction = tensor.dot(x,m)+c
cost = tensor.sum(tensor.pow(prediction - y, 2))/(2 * num_samples)

gradm = tensor.grad(cost, m)
gradc = tensor.grad(cost, c)

learning_rate = 0.01
training_steps = 1000

train = theano.function(inputs = [], outputs = [cost], updates = [(m, m - (learning_rate * gradm)),(c, c - (learning_rate * gradc))])
test = theano.function([], prediction)

t0 = time.time() #start time
for i in range(training_steps):
        costM = train()
        if i % 100 == 0:
                print(costM)
t1 = time.time()
print("Looping %d times took %f seconds" % (training_steps, t1 - t0))

print("Slope :")
print(m.get_value())
print("Intercept :")
print(c.get_value())

#a = numpy.linspace(0, 10, 10)
#b = test(a)

if numpy.any([isinstance(m.op, tensor.Elemwise) and
              ('Gpu' not in type(m.op).__name__)
        for m in train.maker.fgraph.toposort()]):
        print('Used the cpu')
else:
        print('Used the gpu')
        
