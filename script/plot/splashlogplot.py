#!/usr/bin/python
# encoding=utf-8


#!coding:utf-8

import re
import sys
import argparse
import commands
import os
import subprocess
import parse
import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np

class PerfPlotData :
    plotName = "none name"
    logfile = "none path"
    xData = []
    yData = []

    def __init__(self, plotName, logFile, xData, yData, color, marker) :

        """
        namelist        plot数据的标识, 对应各个调度算法[bl-switch, iks, hmp, hmpcb]
        xdata           存储了横轴的数据
        """
        self.plotName = plotName
        self.logFile  = logFile
        self.xData = xData
        self.yData = yData
        self.color = color
        self.marker = marker


def ShowPerfPlot(poltDataList, poly):
    #http://blog.csdn.net/kkxgx/article/details/6951959
    #http://www.mamicode.com/info-detail-280610.html
    #http://blog.csdn.net/panda1234lee/article/details/52311593
    #  中文信息支持
    mpl.rcParams['font.sans-serif'] = ['SimHei'] #用来正常显示中文标签
    mpl.rcParams['axes.unicode_minus'] = False #用来正常显示负号
    #自动调整label显示方式，如果太挤则倾斜显示
    fig = plt.figure(num = 1, figsize = (8, 6))
    fig.autofmt_xdate( )
    #plt.title("Scheduler Bench Performance...")
    plt.title("调度器benchmark")
    plt.xlabel("group", size = 14)
    plt.ylabel("time", size = 14)
    plt.grid( ) # 开启网格

    for data in plotDataList :
        #  设置图表的信息
        print len(data.xData), len(data.yData)
        #  曲线平滑--http://rys1314520.iteye.com/blog/1820777
        #  曲线平滑--http://blog.sina.com.cn/s/blog_142e602960102wegx.html
        if poly == True :
            #计算多项式
            c = np.polyfit(data.xData, data.yData, 10)   #  拟合多项式的系数存储在数组c中
            yy = np.polyval(c, data.xData)                  #  根据多项式求函数值

            #进行曲线绘制
            x_new = np.linspace(0, 1000000, 11)
            f_liner = np.polyval(c,x_new)
            plt.plot(x_new, f_liner, color = data.color, linestyle = '--', marker = data.marker, label = data.plotName)
        else :
            plt.plot(data.xData, data.yData, color = data.color, linestyle = '--', marker = data.marker, label = data.plotName)
        plt.legend(loc = "upper left")
        #plt.savefig('cdf.png', format = 'png')

    plt.show( )



def ParsePlotData(str) :
    # 测试字符串格式化
    # 通过parse库可以实现与format相反的功能
    # 其结果类似与C语言的sscanf
    str_format =  "{:s}{:d}, {:f}"
    xydata = parse.parse(str_format, str)
    #print xydata
    return xydata #(xydata[1], xydata[2])



def ReadPlotXData(minData, maxData, step) :
    #  生成X轴的数据，从minData~maxData，步长为step
    xData = range(minData, maxData,  step)
    return xData;




#----------------------------------
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

        

        pattern = re.compile(reStr, re.S)
        myItems = re.findall(pattern, data)
        #print myItems
        return myItems
    finally:
        pass


def ReadPlotData(filepath) :
    resultdata = readFile(filepath)
    #print resultdata 
    reStr = r"avg = ([0-9]*\.?[0-9]+)"
    myItems = getReItem(resultdata, reStr)
    #print len(myItems), myItems
    return myItems
#----------------------------------


if __name__ == "__main__" :

#python logplot.py -d ../bench  -b messaging -min 10 -max 100 -step 10 -l 5
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
    parser.add_argument("-b", "--bench", dest = "bench", help = "messaging | pipe...")
    parser.add_argument("-a", "--app", dest = "application", help = "messaging | pipe...")
    parser.add_argument("-d", "--dir", dest = "directory", help = "The Directory")
    parser.add_argument("-f", "--file", dest = "resultfile", help = "The file you want to read...")
    parser.add_argument("-min", "--min_group", dest = "min_group", help = "The min group you give...")
    parser.add_argument("-max", "--max_group", dest = "max_group", help = "The max group you give...")
    parser.add_argument("-step", "--step_group", dest = "step_group", help = "The step of the group grown you  give...")
    parser.add_argument("-l", "--loop", dest = "loop", help = "The file you want to read...")
    args = parser.parse_args( )

    #nameTuple = ( "hmp", "hmpcb")
    appTuple = ( "barnes", "fft", "ocean", "radix", "water-spatial", "cholesky", "lu", "radiosity", "raytrace", "water-nsquared")
    nameTuple = ( "bl-switch", "iks", "hmp", "hmpcb")
    #   1）控制颜色
    #   颜色之间的对应关系为
    #   b---blue   c---cyan  g---green    k----black
    #   m---magenta r---red  w---white    y----yellow
    colorTuple = ( 'b', 'c', 'g', 'k', 'm', 'r', 'y', 'y', 'b', 'c')
    
    # plot数据
    # 其中有len(subjectsTuple)个长度为len(nameTuple)的列表
    # 用于标识每个进程subjectsTuple在nameTuple环境下运行的结果集合
    # 买个进程有一个颜色标识
    plotDataList = []  

    #for name in nameTuple :
    for appIndex in range(len(appTuple)) :
        app = appTuple[appIndex]
        color = colorTuple[appIndex]

        #  每个进程的信息
        subPlotDataList = []
        for nameIndex in range(len(nameTuple)) :
            name = nameTuple[nameIndex]
            if (name == "NULL") :
                break
            resultfile = args.directory + "/" + name + "/splash/" + app + "/" + args.loop + ".log"       
            print "\n=========================================="
            print "resultfile :", resultfile

            yData = ReadPlotData(resultfile)
            print "+++++++", len(yData), "+++++++"
            if len(yData) != 1 :
                exit(-1)
            print yData
            print "==========================================\n"
            #plotdata = SplashPlotData(name, resultfile, xData, yData, color, marker)
            #plotDataList.append(plotdata)
            plotDataList.append(yData)

    #ShowPerfPlot(plotDataList, False)
    exit(0)
