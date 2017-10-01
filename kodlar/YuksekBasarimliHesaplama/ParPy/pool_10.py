import multiprocessing as mp
import time

def foo(x):
    sum = 0;
    for i in range(2000000):
        sum = sum + x
    return sum

nop = int(raw_input("Enter the number of processors: "));

pool = mp.Pool(processes=nop)

#version 1: apply
start_time = time.time()
results = [pool.apply(foo, args=(x,)) for x in range(1, 32)] #this creates processes in a synchronized manner
print(results)
print time.time() - start_time, "multiprocesor seconds\n"

#version : map
start_time = time.time()
results = [pool.map(foo, range(1, 32))] #this creates processes in a synchronized manner
print(results)
print time.time() - start_time, "multiprocesor seconds\n"

#version 3: apply_async 
start_time = time.time()
results = [pool.apply_async(foo, args=(x,)) for x in range(1,32)]
results = [p.get() for p in results]
print(results)
print time.time() - start_time, "multiprocesor seconds\n"

#version 4: map_async
start_time = time.time()
results = [pool.map_async(foo, range(1, 32))] #this creates processes in a synchronized manner
results = [p.get() for p in results]
print(results)
print time.time() - start_time, "multiprocesor seconds\n"




