#!/usr/bin/python3

import os
import time
import sys


#Path to fifo
FIFO_PATH = "/tmp/crash.fifo"

def crash():
    if len(sys.argv) == 1:
        print('usage : ./crash.py [test_file]')
        return
    if os.fork() == 0:
        try:
            os.remove(FIFO_PATH)
        except OSError:
            pass
        CMD_PATH = sys.argv[1]
        os.mkfifo(FIFO_PATH)
        f = open(CMD_PATH, 'r')  
        while True:
            fifo = open(FIFO_PATH, 'w')
            line = f.readline()
            if not line:
                break
            fifo.write(line)
            fifo.close()
            time.sleep(0.3)
        os.system('/usr/bin/pkill 42sh')
        sys.exit(0)

if __name__ == "__main__":
    crash()
