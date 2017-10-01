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
print accumulator(10);

new_state = shared(0)
new_accumulator = accumulator.copy(swap={state:new_state})
print new_accumulator(100)
print(new_state.get_value())
print(state.get_value())
