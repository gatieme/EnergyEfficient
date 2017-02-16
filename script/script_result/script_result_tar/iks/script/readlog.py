#!/usr/bin/python
# encoding=utf-8


#!coding:utf-8

import re
import sys
import urllib2
import argparse
import commands
import os
import subprocess



positions = ""
types = ""
numbers = ""
def readFile(file):
    """
    """
    file_object = open(file)

    try :

        read_data = file_object.read( )
        return read_data

    finally :

        file_object.close( )



def writeData(positions, types, nums, sigalrm, sigsegv, sigill) :
    """
    """
    resultfile = "./RESULT/" + nums + "/result.log"
    file_object = open(resultfile, "a")
    file_object.write(positions.center(10) + types.center(20) + str(sigalrm).center(10) + str(sigsegv).center(10) + str(sigill).center(10) + "\n")
    file_object.close( )





def getReItem(data) :
    """
    """
    try:
        #  匹配的信息如下
        #  Total time: 0.038 [sec]
        #reStr = r'Total time: ([-+]?[0-9]*\.?[0-9]+) [sec]'
        reStr = r'Total time: ([0-9]*\.?[0-9]+)'

        pattern = re.compile(reStr, re.S)
        myItems = re.findall(pattern, data)

        return myItems
    finally:
        pass


def getAvgResult(myItems):
    sum = 0.0
    for item in myItems :
        sum += float(item)
    avg = sum / len(myItems)
    #print "sum = %f, avg = %f" % (sum, avg)

    return avg




if __name__ == "__main__" :
    # 测试正则表达式

    reload(sys)
    sys.setdefaultencoding("utf-8")
    if len(sys.argv) > 1:               #  如果在程序运行时，传递了命令行参数
        pass
        #  打印传递的命令行参数的信息
        #print "您输入的所有参数共 %d 个，信息为 sys.argv = %s" % (len(sys.argv), sys.argv)

        #for i, eachArg in enumerate(sys.argv):
        #    print "[%d] = %s" % (i, eachArg)
    else:
        print "Useage : read.py file..."
        exit(0)

    parser = argparse.ArgumentParser( )
    #parser.add_argument("-n", "--name", dest = "name", help = "bl-switch | iks | hmp | hmpcb...")
    parser.add_argument("-d", "--dir", dest = "directory", help = "The Directory")
    parser.add_argument("-b", "--bench", dest = "bench", help = "messaging | pipe...")
    parser.add_argument("-f", "--file", dest = "resultfile", help = "The file you want to read...")
    parser.add_argument("-min", "--min_group", dest = "min_group", help = "The min group you give...")
    parser.add_argument("-max", "--max_group", dest = "max_group", help = "The max group you give...")
    parser.add_argument("-step", "--step_group", dest = "step_group", help = "The step of the group grown you  give...")
    parser.add_argument("-g", "--curr_group", dest = "curr_group", help = "The step of the group grown you  give...")
    parser.add_argument("-l", "--loop", dest = "loop", help = "The file you want to read...")
    args = parser.parse_args( )

    if (args.resultfile == None) :
        resultfile = args.directory + "/perf/" + args.bench + "/"                                           \
                   + args.min_group + "-" + args.max_group + "-" + args.step_group + "-" +args.loop + "/"   \
                   + args.curr_group + ".log"
    else :
        resultfile = args.resultfile

    #print resultfile
    resultdata = readFile(resultfile)
    #print resultdata
    myItems = getReItem(resultdata)
    #print len(myItems), myItems

    avg = getAvgResult(myItems)
    if ((int(args.min_group) + int(args.step_group)) > int(args.max_group)) :  #  同一个循环多次
        print "avg = %f" % (avg)
        for i in range(len(myItems)) :
            print "%4d, %f" % (i + 1, float(myItems[i]))
    else :
        if (len(myItems) != int(args.loop)) :
            print "miss something in read %sm, len = %d" % (resultfile, len(myItems))
            exit(-1)

        print " %4s, %f" %(args.curr_group, avg)
    
    exit(0)

