import time
import multiprocessing
 
def my_function():
    time.sleep(3)
    print "my_function is done!"
 
if __name__ == '__main__':
    process = multiprocessing.Process(target=my_function)
    process.start()
    process.join()
    print "__main__ is done!"
