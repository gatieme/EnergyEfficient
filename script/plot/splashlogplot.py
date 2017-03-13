#!/usr/bin/python
# encoding=utf-8


#!coding:utf-8
#http://www.huochai.mobi/p/d/1601065/?share_tid=874fc167e1fe&fmid=
#https://segmentfault.com/a/1190000004103325
#
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
import string

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


#----------------------------------
#
#   读取数据绘制plot图表
#
#----------------------------------


# 添加数据标签
def AddPlotLabels(xdata, ydata, width, color, name):
    """
    xdaya : x轴的数据
    ydata : y轴的数据
    width : 柱状图的宽度
    color : 柱状图的颜色
    name  : 柱状图的名称
    """
    rects = plt.bar(xdata, ydata, width, color = color, label = name)#, align = "center")

    #  柱状图上显示text信息
    #  plt.text的参数分别是：x坐标，y坐标，要显示的文字
    #for rect in rects:
    #    height = rect.get_height( )
    #    plt.text(rect.get_x() + rect.get_width() / 2, height, height, ha='center', va='bottom')
    #    # 柱形图边缘用白色填充，纯粹为了美观
    #    rect.set_edgecolor('white')


def ShowPerfPlot(nameTuple, appTuple, poltDataList, colorTuple, standardized = True, minY = 0, maxY = 4200):

    if standardized == True :
        StandardizedPlotDataList(plotDataList)
    
    #自动调整label显示方式，如果太挤则倾斜显示
    fig = plt.figure(num = 1, figsize = (8, 6))
    fig.autofmt_xdate( )
    plt.title("scheduler splash benchmark/runtime")
    plt.ylabel("time(ms)", size = 14)
    plt.grid( ) # 开启网格
    # 必须配置中文字体，否则会显示成方块
    # 注意所有希望图表显示的中文必须为unicode格式
    # http://blog.sciencenet.cn/blog-43412-343002.html
    # https://segmentfault.com/a/1190000004103325
    # http://www.jianshu.com/p/8c0fe1240e78
    #custom_font = mpl.font_manager.FontProperties(fname='SimHei')
    #font_size = 10 # 字体大小
    #fig_size = (8, 6) # 图表大小
    #mpl.rcParams['font.sans-serif'] = ['SimHei'] #用来正常显示中文标签
    #mpl.rcParams['axes.unicode_minus'] = False #用来正常显示负号
    

    # 设置柱形图宽度
    bar_width = 0.2

    xdata = np.arange(len(appTuple))   # 

    print "\n==============================================================="
    print "+++++++ plot data +++++++"
    for nameIndex in range(len(nameTuple)) :
        print nameIndex, plotDataList[nameIndex]
        AddPlotLabels(xdata + bar_width * nameIndex, poltDataList[nameIndex], bar_width, \
            colorTuple[nameIndex], nameTuple[nameIndex])
    print "===============================================================\n"

    # X轴标题
    # xdata + bar_width * len(nameTuple) / 2 使得x的标签在中间开始显示
    plt.xticks(xdata + bar_width * len(nameTuple) / 2, appTuple)#, fontproperties=custom_font)
    # Y轴范围
    plt.ylim(minY, maxY)


    # 图表标题
    #plt.title(u'调度器')#, fontproperties=custom_font)
    # 图例显示在图表下方
    plt.legend(loc='upper center', bbox_to_anchor=(0.5, -0.03), fancybox=True, ncol=5)#, prop=custom_font)

    # 图表输出到本地
    plt.show( )



def ReadPlotXData(minData, maxData, step) :
    #  生成X轴的数据，从minData~maxData，步长为step
    xData = range(minData, maxData,  step)
    return xData;



#----------------------------------
#
#   将数据标准化
#
##----------------------------------


#http://blog.csdn.net/kryolith/article/details/39770187
def MaxMinNormalization(x, Min, Max):  
    x = (x - Min) / (Max - Min);  
    return x;  

def StandardizedPlotDataList(plotDataList) :
    """
    每个name系统中各个进程app的运行情况
    每行对应一个系统
    每列对应一个进程
    由于各个进行运行的时间差异比较大
    为了在一个图形上显示的比较好看因此将这些数据进行标准化

    http://blog.csdn.net/kryolith/article/details/39770187
    """

    for col in range(len(plotDataList[0]))  :       #  每列代表一个进程app
        colList = []        
        for row in range(len(plotDataList)) :      #  每行代表一个系统name
            colList.append(plotDataList[row][col])
        print "col = ", col, colList

        minData = min(colList) * 1.0
        maxData = max(colList) * 1.0
        for row in range(len(plotDataList)) :      #  每行代表一个系统name
            #tmp =  MaxMinNormalization(plotDataList[row][col], minData, maxData)
            #plotDataList[row][col] = tmp
            #plotDataList[row][col] = plotDataList[row][col] / (maxData * 1.1)
            plotDataList[row][col] = plotDataList[row][col] / plotDataList[len(plotDataList) - 1][col]




#-----------------------------------
#
#   从log中读取并处理数据
#
#-----------------------------------
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
    #parser.add_argument("-n", "--name", dest = "name", help = "bl-switch | iks | hmp | hmpdb...")
    parser.add_argument("-b", "--bench", dest = "bench", help = "messaging | pipe...")
    parser.add_argument("-a", "--app", dest = "application", help = "messaging | pipe...")
    parser.add_argument("-d", "--dir", dest = "directory", help = "The Directory")
    parser.add_argument("-f", "--file", dest = "resultfile", help = "The file you want to read...")
    parser.add_argument("-min", "--min_group", dest = "min_group", help = "The min group you give...")
    parser.add_argument("-max", "--max_group", dest = "max_group", help = "The max group you give...")
    parser.add_argument("-step", "--step_group", dest = "step_group", help = "The step of the group grown you  give...")
    parser.add_argument("-l", "--loop", dest = "loop", help = "The file you want to read...")
    args = parser.parse_args( )

    #nameTuple = ( "hmp", "hmpdb")
    #appTuple = ( "fft", "radix", "cholesky" )  #300
    #appTuple = ( "cholesky", "fft", "radix", "lu", "ocean", "radiosity", "barnes", "raytrace", "water-ns", "water-s") # 2000
    appTuple = ( "radix", "radiosity", "water-ns", "lu", "cholesky", "fft", "water-s", "barnes", "ocean", "raytrace") # nice
    #appTuple = ( "barnes", "ocean", "water-spatial", "lu", "radiosity", "raytrace", "water-nsquared")
    #appTuple = ( "barnes", "ocean", "water-s", "lu", "radiosity", "raytrace", "water-ns")
    #appTuple = ( "ocean", "water-s", "lu", "radiosity", "raytrace", "water-ns")
    
    nameTuple = ( "bl-switch", "iks", "hmp", "hmpdb")
    #nameTuple = ( "big", "little", "hmp", "hmpdb")
    #nameTuple = ( "big", "little", "bl-switch", "iks", "hmp", "hmpdb")
    #   1）控制颜色
    #   颜色之间的对应关系为
    #   b---blue   c---cyan  g---green    k----black
    #   m---magenta r---red  w---white    y----yellow
    #colorTuple = ( 'r', 'b', 'y', 'k', 'g', 'c', 'm', 'r', 'y', 'y', 'b', 'c')
    colorTuple = ( '#CCCCCC', '#CC6666', '#1DACD6', '#6E5160', '#', 'k', 'g', 'c', 'm', 'r', 'y', 'y', 'b', 'c')
    
    # plot数据
    # 其中有len(subjectsTuple)个长度为len(nameTuple)的列表
    # 用于标识每个进程subjectsTuple在nameTuple环境下运行的结果集合
    # 买个进程有一个颜色标识
    plotDataList = []  

    print "\n==============================================================="
    print "+++++++ read plot data +++++++"
    #for name in nameTuple :
    for nameIndex in range(len(nameTuple)) :
        name = nameTuple[nameIndex]
        color = colorTuple[nameIndex]

        #  每个进程的信息
        appPlotDataList = []
        for appIndex in range(len(appTuple)) :
            app = appTuple[appIndex]
            if (name == "NULL") :
                break
            resultfile = args.directory + "/" + name + "/splash/" + app + "/" + args.loop + ".log"       
            #print "\n=========================================="
            #print "resultfile :", resultfile

            yData = ReadPlotData(resultfile)
            #print "+++++++", len(yData), "+++++++"
            if len(yData) != 1 :
                exit(-1)
            #print yData
            #print "==========================================\n"

            appPlotDataList.append(string.atof(yData[0]))   #  每个进程的运行情况
        print name, appPlotDataList
        #plotdata = SplashPlotData(name = app, xData = , yData = appPlotDataList, color = color)
        plotDataList.append(appPlotDataList)    # 每个name系统中各个进程app的运行情况, 每行对应一个系统, 每列对应一个进程
    print "===============================================================\n" 

    print "\n===============================================================" 
    print "+++++++ all data you get +++++++"
    print "name =", nameTuple
    print "app =", appTuple
    print "data =", plotDataList
    print "color =", colorTuple
    print "===============================================================\n" 
    
    #ShowPerfPlot(nameTuple, appTuple, plotDataList, colorTuple, standardized = False, minY = 0, maxY = 4200)
    ShowPerfPlot(nameTuple, appTuple, plotDataList, colorTuple, standardized = True, minY = 0, maxY = 3.5)
    exit(0)
