import uuid
import multiprocessing
 
def my_function(worker_id):
    print 'My Worker Id is: {0}'.format(worker_id)
 
if __name__ == '__main__':
    for x in range(1600000):
        process = multiprocessing.Process(target=my_function, args=(uuid.uuid1(),))
        process.start()
