#!/usr/bin/python3

import os
import time


#Path to the commands file
CMD_PATH = "/Users/onouaman/Desktop/projects/Git/42sh/crash"
#Path to fifo
FIFO_PATH = "/tmp/crash.fifo"

def crash():
    try:
        os.remove(FIFO_PATH)
    except OSError:
        pass
    os.mkfifo(FIFO_PATH)
    f = open(CMD_PATH, 'r')
    
    while True:
        fifo = open(FIFO_PATH, 'w')
        line = f.readline()
        if not line:
            break
        fifo.write(line)
        fifo.close()
        time.sleep(0.2)
    os.system('/usr/bin/pkill 42sh')
if __name__ == "__main__":
    crash()
