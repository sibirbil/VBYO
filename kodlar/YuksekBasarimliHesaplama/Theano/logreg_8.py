import numpy
import theano
import theano.tensor as T
import time

rng = numpy.random

N = 5000                                 # training sample size - #rows
feats = 1000                             # number of input variables - #features

# generate a dataset: D = (input_values, target_class)
D = (rng.randn(N, feats), rng.randint(size=N, low=0, high=2)) #randn - univariate
                      #"normal" (Gaussian) distribution of mean 0 and variance 1
training_steps = 200 #increase this for better accuracy

# Declare Theano symbolic variables
x = T.dmatrix("x")
y = T.dvector("y")

# initialize the weight vector w randomly
w = theano.shared(rng.randn(feats), name="w")

# this and the following bias variable b
# are shared so they keep their values
# between training iterations (updates)

# initialize the bias term
b = theano.shared(0., name="b")

print("Initial model:")
print(w.get_value())
print(b.get_value())

# Construct Theano expression graph
p_1 = 1 / (1 + T.exp(-T.dot(x, w) - b))         # Probability that target = 1
prediction = p_1 > 0.5                          # The prediction thresholded
xent = -y * T.log(p_1) - (1-y) * T.log(1 - p_1) # Cross-entropy loss function
cost = xent.mean() + 0.01 * (w ** 2).sum()      # The cost to minimize
gw, gb = T.grad(cost, [w, b])                   # Compute the gradient of the cost

rmse = ((y - p_1) ** 2).mean()

# w.r.t weight vector w and
# bias term b
# (we shall return to this in a
# following section of this tutorial)

# Compile
train = theano.function(
    inputs=[x,y],
    outputs=[prediction, xent],
    updates=((w, w - 0.1 * gw), (b, b - 0.1 * gb)))

predict = theano.function(inputs=[x], outputs=prediction)

accu = theano.function(inputs=[x,y], outputs = [rmse]) 

#initial predictions
Pi = predict(D[0])

# Train
tic = time.time()
for i in range(training_steps):
    pred, err = train(D[0], D[1])
    err2 = accu(D[0], D[1]);
    print "Iteration: " + str(i) + " " + str(err2)
print("Done in %f seconds" %(time.time() - tic))
    
#print("Final model: ")
#print(w.get_value())
#print(b.get_value())

#final prediction
#print("prediction on D: ")
#Ps = predict(D[0])
#for i in range(N):
#    print(Pi[i], Ps[i], D[1][i], D[1][i] == Ps[i])

