#functions with internal state
import theano
import theano.tensor as T
from theano import shared
from theano import function

#The shared keyword constructs so-called shared variables.
#These are hybrid symbolic and non-symbolic variables whose value may be shared between multiple functions.
state = shared(0)

#integer
inc = T.iscalar('inc')

#updates must be supplied with a list of pairs of the form (shared-variable, new expression).
#It can also be a dictionary whose keys are shared-variables and values are the new expressions.
#Either way, it means whenever this function runs, it will replace the
#value of each shared variable with the result of the corresponding expression.

accumulator = function([inc], state, updates=[(state, state + inc)])

print "value: ", state.get_value()
print "acc 1: ", accumulator(1)
print "value: ", state.get_value()
print "acc 300: ", accumulator(300)
print "value: ", state.get_value()
print '-' * 50

state.set_value(-1)
print "acc 3: ", accumulator(3)
print "value: ", state.get_value()
print '-' * 50

decrementor = function([inc], state, updates=[(state, state-inc)])
print "dec 20: ", decrementor(20)
print "value: ", state.get_value()
print '-' * 50


fn_of_state = state * 2 + inc
foo = T.scalar(dtype=state.dtype)

#It may happen that you expressed some formula using a shared variable, but you do not want to use its value.
#In this case, you can use the givens parameter of function which replaces a particular node in a graph
#for the purpose of one particular function.
skip_shared_a = function([inc, foo], fn_of_state, givens=[(state, foo)])
#skip_shared_b = function([inc, state], fn_of_state) # TypeError: Cannot use a shared variable (<TensorType(int64, scalar)>) as explicit input.
skip_shared_c = function([inc], [fn_of_state]) 
print "ssa 1,3: ", skip_shared_a(1, 3)
print "ssc 1: ", skip_shared_c(1)
print "value: ", state.get_value()
print '-' * 50
