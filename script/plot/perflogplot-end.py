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
        namelist        plot数据的标识, 对应各个调度算法[bl-switch, iks, hmp, hmpdb]
        xdata           存储了横轴的数据
        """
        self.plotName = plotName
        self.logFile  = logFile
        self.xData = xData
        self.yData = yData
        self.color = color
        self.marker = marker


def ShowPerfPlot(plotDataList, poly, numRows, numCols, plotNum):
    #http://blog.csdn.net/kkxgx/article/details/6951959
    #http://www.mamicode.com/info-detail-280610.html
    #http://blog.csdn.net/panda1234lee/article/details/52311593
    #  中文信息支持
    mpl.rcParams['font.sans-serif'] = ['SimHei'] #用来正常显示中文标签
    mpl.rcParams['axes.unicode_minus'] = False #用来正常显示负号
    #自动调整label显示方式，如果太挤则倾斜显示

    plt.subplot(numRows, numCols, plotNum)  
    #plt.title("Scheduler Bench Performance...")
    title_str = "scheduler performance test(perf/messaging)"
    #plt.title(title_str)
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
        #plt.legend(loc = "upper left")

    #plt.savefig(title_str + '.png', format = 'png')
    #plt.show( )



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


def ReadPlotData(filepath, lines, iszero) :
    fileobject = open(filepath)

    if iszero == True :
        xData = [ 0 ]
        yData = [ 0 ]
    else :
        xData = [ ]
        yData = [ ]
    while 1 :
        linedata = fileobject.readlines(lines)

        if not linedata:
            break
        for line in linedata:
            #print line
            xyData = ParsePlotData(line)
            if (xyData != None) :
                #print "data = ", xyData[0], xyData[1]
                xData.append(xyData[1])
                yData.append(xyData[2])
            else :
                #print "line = ", line
                pass
    return (xData, yData)


#def PerfBenchPlotRun(nameTuple, colorTuple, marketTuple, bench, ming, maxg, setg) :
#def PerfBenchPlotRun(nameTuple, colorTuple, marketTuple, \
def PerfBenchPlotRun(directory, bench, min_group, max_group, step_group, loop,  \
                    numRows, numCols, plotNum) :
    plotDataList = []
    #for name in nameTuple :
    for index in range(len(nameTuple)) :
        name = nameTuple[index]
        color = colorTuple[index]
        marker = markerTuple[index]
        if (name == "NULL") :
            break
        resultfile = directory + "/" + name + "/perf/" + bench + "/" \
                   + min_group + "-" + max_group + "-" + step_group + "-" + loop + ".log"
        print "\n=========================================="
        print "resultfile :", resultfile

        if ((int(min_group) + int(step_group)) > int(max_group)) :  #  同一个循环多次
            iszero = False
        else :
            iszero = True
        (xData, yData) = ReadPlotData(resultfile, 1000, iszero)
        print "+++++++", len(xData), len(yData), "+++++++"
        print xData
        print yData
        print "==========================================\n"
        plotdata = PerfPlotData(name, resultfile, xData, yData, color, marker)
        plotDataList.append(plotdata)

    ShowPerfPlot(plotDataList, False, numRows, numCols, plotNum)



if __name__ == "__main__" :

#python logplot.py -d ../bench  -b messaging -min 10 -max 100 -step 10 -l 5
    reload(sys)
    sys.setdefaultencoding("utf-8")

    #nameTuple = ( "hmp", "hmpdb")
    nameTuple = ( "bl-switch", "iks", "hmp", "hmpdb")
    #nameTuple = ( "bl-switch", "iks", "hmp", "hmpdb", "little-cluster", "big-cluster", "big-little-cluster")
    #nameTuple = ( "little-cluster", "big-cluster", "big-little-cluster")
    #   1）控制颜色
    #   颜色之间的对应关系为
    #   b---blue   c---cyan  g---green    k----black
    #   m---magenta r---red  w---white    y----yellow
    colorTuple = ( 'b', 'c', 'g', 'k', 'm', 'r', 'y', 'y')
    #.  Point marker
    #,  Pixel marker
    #o  Circle marker
    #v  Triangle down marker
    #^  Triangle up marker
    #<  Triangle left marker
    #>  Triangle right marker
    #1  Tripod down marker
    #2  Tripod up marker
    #3  Tripod left marker
    #4  Tripod right marker
    #s  Square marker
    #p  Pentagon marker
    #*  Star marker
    #h  Hexagon marker
    #H  Rotated hexagon D Diamond marker
    #d  Thin diamond marker
    #| Vertical line (vlinesymbol) marker
    #_  Horizontal line (hline symbol) marker
    #+  Plus marker
    #x  Cross (x) marker
    markerTuple= ( 'o', '^', '*', 's', 'p', '2', 'h', )
    
    fig = plt.figure(num = 1, figsize = (6, 5))
    fig.autofmt_xdate( )
    PerfBenchPlotRun("../bench", "messaging",  "10",  "10", "5", "100", 3, 2, 1)    
    PerfBenchPlotRun("../bench", "messaging",  "20",  "20", "5", "100", 3, 2, 2)    
    PerfBenchPlotRun("../bench", "messaging",  "50",  "50", "5", "100", 3, 2, 3)    
    PerfBenchPlotRun("../bench", "messaging", "100", "100", "5", "100", 3, 2, 4)
    PerfBenchPlotRun("../bench", "messaging",   "5", "200", "5",   "5", 3, 1, 3)
    plt.legend(loc = "center")

    fig = plt.figure(num = 2, figsize = (6, 5))
    fig.autofmt_xdate( )
    PerfBenchPlotRun("../bench", "pipe",  "1000",  "1000", "5", "100", 3, 2, 1)    
    PerfBenchPlotRun("../bench", "pipe",  "10000",  "10000", "5", "100", 3, 2, 2)    
    PerfBenchPlotRun("../bench", "pipe",  "100000",  "100000", "5", "100", 3, 2, 3)    
    PerfBenchPlotRun("../bench", "pipe", "1000000", "1000000", "5", "100", 3, 2, 4)
    PerfBenchPlotRun("../bench", "pipe",   "100000", "1000000", "100000",   "10", 3, 1, 3)
    plt.legend(loc = "lower center")

    plt.show( )  
    exit(0)
