import uuid
import multiprocessing
 
def my_function():
    print 'My Unique Id: {0}'.format(uuid.uuid1())
 
if __name__ == '__main__':
    for x in range(16):
        process = multiprocessing.Process(target=my_function)
        process.start()

