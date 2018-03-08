#!/usr/bin/env python


import logging  
import logging.handlers 
import time
import multiprocessing
import os

  
#logger.info('first info message')  
#logger.debug('first debug message')  
#
def log_init(log_path):
    LOG_FILE = log_path + ".log"
  
    handler = logging.handlers.RotatingFileHandler(LOG_FILE, maxBytes = 1024*1024, backupCount = 1)
    fmt = '%(asctime)s -%(process)s - %(filename)s:%(lineno)s - %(message)s'  
  
    formatter = logging.Formatter(fmt)
    handler.setFormatter(formatter)
  
    log = logging.getLogger(os.path.basename(log_path))
    log.addHandler(handler)
    log.setLevel(logging.DEBUG) #DEBUG, INFO, WARNING, ERROR, CRITICAL
    return log


def writer_proc(q):      
    log = log_init("write")
    try:         
        log.info("write, pid: %s" % os.getpid())
        q.put("abc", block = False)
        q.put("xyz", block = False) 
    except:         
        pass   

def reader_proc(q): 
    log = log_init("read")     
    try:         
        log.error("read, pid: %s" % os.getpid())
        time.sleep(1)
        log.error(q.get(block = True))
    except:         
        pass

if __name__ == "__main__":
    q = multiprocessing.Queue()
    writer = multiprocessing.Process(target=writer_proc, args=(q,))  
    writer.start()   

    log = log_init("main")
    log.error("main")

    reader = multiprocessing.Process(target=reader_proc, args=(q,))  
    reader.start()  

#    reader2 = multiprocessing.Process(target=reader_proc, args=(q,))  
#    reader2.start()  

    reader.join()  
 #   reader2.join()  
    writer.join()
