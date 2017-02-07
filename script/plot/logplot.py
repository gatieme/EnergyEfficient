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

#  经验累计分布函数cumulative distribution function
def ShowCDFPlot(xdata, ydata):
    """
    step  步长
    """

    #  设置图表的信息
    plt.figure(num = 1, figsize = (8, 6))
    plt.title("Scheduler Bench Performance...")
    plt.xlabel("group", size = 14)
    plt.ylabel("time", size = 14)

    plt.plot(xdata, ydata, color = 'r', linestyle = '-', label = "cfs")

    plt.legend(loc = "upper left")
    #plt.savefig('cdf.png', format = 'png')
    plt.show()






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
    parser.add_argument("-n", "--name", dest = "name", help = "bl-switch | iks | hmp | hmpcb...")
    parser.add_argument("-b", "--bench", dest = "bench", help = "messaging | pipe...")
    parser.add_argument("-d", "--dir", dest = "directory", help = "The Directory")
    parser.add_argument("-f", "--file", dest = "resultfile", help = "The file you want to read...")
    parser.add_argument("-min", "--min_group", dest = "min_group", help = "The min group you give...")
    parser.add_argument("-max", "--max_group", dest = "max_group", help = "The max group you give...")
    parser.add_argument("-step", "--step_group", dest = "step_group", help = "The step of the group grown you  give...")
    parser.add_argument("-l", "--loop", dest = "loop", help = "The file you want to read...")
    args = parser.parse_args( )

    resultfile = args.directory + "/" + args.name + "/perf/" + args.bench + "/"
               + args.min_group + "-" + args.max_group + "-" +args.loop + ".log"
    print "resultfile :", resultfile
    #resultfile = args.resultfile

    #print resultfile


    exit(0)
