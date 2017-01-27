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


def getResult(myItems):
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
    parser.add_argument("-u", "--user", dest = "user", help = "Who you want to read...")
    parser.add_argument("-f", "--file", dest = "resultfile", help = "The file you want to read...")
    parser.add_argument("-m", "--max_group", dest = "max_group", help = "The file you want to read...")
    parser.add_argument("-g", "--group", dest = "group", help = "The file you want to read...")
    parser.add_argument("-l", "--loop", dest = "loop", help = "The file you want to read...")
    args = parser.parse_args( )

    resultfile = "./RESULT/" + args.user + "/" +args.max_group + "-" +args.loop + "/" + args.group + ".log"

    #print resultfile
    resultdata = readFile(resultfile)
    #print resultdata
    myItems = getReItem(resultdata)
    #print len(myItems), myItems
    if (len(myItems) != int(args.loop)) :
        print "miss something in read %s" % (resultfile)
        exit(-1)
    result = getResult(myItems)
    print "%4s, %f" %(args.group, result)
    exit(0)

