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




# 取出数据data, 符合正则表达式的数据
def getReItem(data, reStr) :
    """
    """
    try:
        #  匹配的信息如下
        #  Total time: 0.038 [sec]
        #reStr = r'Total time: ([-+]?[0-9]*\.?[0-9]+) [sec]'

        #reStr = r'Total time: ([0-9]*\.?[0-9]+)'

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


def PrintResult(myItems, title, islist) :
    avg = getAvgResult(myItems)
    if islist == True :  # 输出列中每一行的数据
        print "avg = %f" % (avg)
        for i in range(len(myItems)) :
            print "%4d, %f" % (i + 1, float(myItems[i]))
    else :              # 按照个数输出平均数, 标题为
        if (len(myItems) != int(args.loop)) :
            print "miss something in read %sm, len = %d" % (resultfile, len(myItems))
            exit(-1)
        if (args.curr_group != None) :
            print " %4s, %f" %(args.curr_group, avg)
        else :
            print "avg = %d" % int(avg)


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
    parser.add_argument("-d", "--dir", dest = "directory", help = "The Directory")
    parser.add_argument("-b", "--bench", dest = "bench", help = "messaging | pipe...")
    parser.add_argument("-a", "--app", dest = "application", help = "messaging | pipe...")
    parser.add_argument("-f", "--file", dest = "resultfile", help = "The file you want to read...")
    parser.add_argument("-min", "--min_group", dest = "min_group", help = "The min group you give...")
    parser.add_argument("-max", "--max_group", dest = "max_group", help = "The max group you give...")
    parser.add_argument("-step", "--step_group", dest = "step_group", help = "The step of the group grown you  give...")
    parser.add_argument("-g", "--curr_group", dest = "curr_group", help = "The step of the group grown you  give...")
    parser.add_argument("-l", "--loop", dest = "loop", help = "The file you want to read...")
    args = parser.parse_args( )

    if (args.resultfile == None) :
        if (args.bench == "perf") :
            resultfile = args.directory + "/" + args.bench + "/" + args.application + "/"                       \
                       + args.min_group + "-" + args.max_group + "-" + args.step_group + "-" +args.loop + "/"   \
                       + args.curr_group + ".log"
        elif (args.bench == "splash") :
            resultfile = args.directory + "/" + args.bench + "/" + args.application + "/" + args.loop + "/" + args.loop + ".log"
        else :
            print "error bench"
            exit(-1)
    else :
        resultfile = args.resultfile
    #-------------------------------------------------
    #   不同的application输出不一致,
    #   因此需要使用不同的正则表达式来匹配输出
    #   application  : resrt
    #-------------------------------------------------
    reStrTable = {
        # perf
        "messaging"     :   r"Total time: ([0-9]*\.?[0-9]+)",
        "pipe"          :   r"Total time: ([0-9]*\.?[0-9]+)",
        # splash
        "barnes"        :   u"COMPUTETIME\s+=\s+([0-9]+)",
        "fft"           :   u"Total time with initialization\s+:\s+([0-9]+)",
        "radiosity"     :   u"\s+Total time with initialization\s+([0-9]+)",
        "raytrace"      :   u"\s+Total time with initialization\s+([0-9]+)",
        "water-spatial" :   u"COMPUTETIME \(after initialization\)\s+=\s+([0-9]+)",
        "cholesky"      :   u"Total time with initialization\s+:\s+([0-9]+)",
        "lu"            :   u"Total time with initialization\s+:\s+([0-9]+)",
        "ocean"         :   u"Total time with initialization\s+:\s+([0-9]+)",
        "radix"         :   u"Total time with initialization\s+:\s+([0-9]+)",
        "water-nsquared":   u"COMPUTETIME \(after initialization\)\s+=\s+([0-9]+)",
    }
    #print resultfile
    resultdata = readFile(resultfile)
    ##print "resultfile = ", resultfile
    ##print "restr = \"%s\"" % (reStrTable[args.application])
    myItems = getReItem(resultdata, reStrTable[args.application])
    ##print len(myItems), myItems

    if (args.bench == "splash" or (args.bench == "perf" and (int(args.min_group) + int(args.step_group)) > int(args.max_group))) :  #  同一个循环多次
        PrintResult(myItems, args.curr_group, True)   # 列表输出
    else :
        PrintResult(myItems, args.curr_group, False)  # 只输出一行数据
    exit(0)

