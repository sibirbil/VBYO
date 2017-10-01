import theano
import theano.tensor as T
import numpy as np
import time

#scan: A general form of recurrence, which can be used for looping.
#You scan a function along some input sequence, producing an output at each time-step.

#The function can see the previous K time-steps of your function.
#sum() could be computed by scanning the z + x(i) function over a list, given an initial state of z=0.

#Often a for loop can be expressed as a scan() operation, and scan is the closest that Theano comes to looping.
#Advantages of using scan over for loops:
# - Number of iterations to be part of the symbolic graph.
# - Minimizes GPU transfers (if GPU is involved).
# - Computes gradients through sequential steps.
# - Slightly faster than using a for loop in Python with a compiled Theano function.
# - Can lower the overall memory usage by detecting the actual amount of memory needed.

# define tensor variable
X = T.matrix("X")
results, updates = theano.scan(lambda x_i: T.sqrt((x_i ** 2).sum()), sequences=[X])
compute_norm_lines = theano.function(inputs=[X], outputs=results)

n = 1000

# test value
x = np.eye(1000, dtype=theano.config.floatX)

tic = time.time()
A = compute_norm_lines(x)
print('It took %f seconds' % (time.time() - tic))

# comparison with numpy
tic = time.time()
B = np.sqrt((x ** 2).sum(1))
print('It took %f seconds' % (time.time() - tic))

print '-' * 50

coefficients = theano.tensor.vector("coefficients")
x = T.scalar("x")

max_coefficients_supported = 10000

# Generate the components of the polynomial
components, updates = theano.scan(fn=lambda coefficient, power, free_variable: coefficient * (free_variable ** power),
                                  sequences=[coefficients, theano.tensor.arange(max_coefficients_supported)],
                                  non_sequences=x)

# Sum them up
polynomial = components.sum()

# Compile a function
calculate_polynomial = theano.function(inputs=[coefficients, x], outputs=polynomial)

# Test
test_coefficients = np.asarray([1, 0, 2], dtype=np.float32)
test_value = 3
print(calculate_polynomial(test_coefficients, test_value))
print(1.0 * (3 ** 0) + 0.0 * (3 ** 1) + 2.0 * (3 ** 2))
