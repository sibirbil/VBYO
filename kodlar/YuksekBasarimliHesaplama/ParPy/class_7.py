import multiprocessing
 
class My_Class(multiprocessing.Process): 
    def run(self):
        print 'Hello from a class'
        return
 
if __name__ == '__main__':
    process = My_Class()
    process.start()
