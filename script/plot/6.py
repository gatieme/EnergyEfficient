#!/usr/bin/python
# encoding=utf-8
import random
import time

#100 200 300 400 500 600 700 800 900 1000
# 0  10  30   50  70  70  50  30  10   0

def getLength(num) :
    length = (50 - fabs(num - 500) / 10)  


if __name__ == '__main__':
    MAX = 1023
    MIN = 0
    up_threshold = 700
    down_threshold = 512

    while True :
        cap_big = random.uniform(down_threshold, MAX) 
        ncap_big =  MAX - cap_big
        len_big = random.randint(0, 100)
        if up_threshold > 900 :
            pass
            cap_big = 0
            ncap_big = 1023
            len_big = 1
        print "==big==", cap_big, ncap_big, len_big
        

        cap_little =  random.uniform(0, up_threshold)  
        ncap_little = up_threshold - cap_little
        len_little = random.randint(0, 100) 
        print "==LITTLE==", cap_little, ncap_little, len_little

        #cap_cluster = cap_big / (cap_big + cap_little)
        #cap_length = (cap_big * len_big * 1.0) / (cap_big * len_big + cap_little * len_little)

        ncap_cluster = ncap_big / (ncap_big + ncap_little)
        #ncap_length = (ncap_big * (len_big  + 1)* 1.0) / (ncap_big * (len_big + 1) + ncap_little * len_little)
        ncap_length = ((len_big + 1)* 1.0)  / (len_big + len_little + 1)
        print ncap_cluster, ncap_length
        #up_threshold = hmp_up_threshold - diff * cap_cluster * cap_length
        #down_threshold = hmp_down_threshold + diff * (1 - cap_cluster) * (1 - cap_length)
        up_threshold = MAX - MAX * (1 - ncap_cluster) * (1 - ncap_length)
        down_threshold = MAX * ncap_cluster * ncap_length
        if up_threshold < down_threshold :
            print "error"
        else :
            print "===", up_threshold, down_threshold
        time.sleep(1)
