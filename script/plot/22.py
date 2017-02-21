#!/usr/bin/env python
# encoding=utf-8

#!/usr/bin/env python
# coding: utf-8


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


# 添加数据标签
def add_labels(xdata, ydata, width, color, name):
    """
    xdaya : x轴的数据
    ydata : y轴的数据
    width : 柱状图的宽度
    color : 柱状图的颜色
    name  : 柱状图的名称
    """
    rects = plt.bar(xdata, ydata, width, color = color, label = name)

    for rect in rects:
        height = rect.get_height()
        plt.text(rect.get_x() + rect.get_width() / 2, height, height, ha='center', va='bottom')
        # 柱形图边缘用白色填充，纯粹为了美观
        rect.set_edgecolor('white')


if __name__ == '__main__':
    # 必须配置中文字体，否则会显示成方块
    # 注意所有希望图表显示的中文必须为unicode格式
    # http://blog.sciencenet.cn/blog-43412-343002.html
    # https://segmentfault.com/a/1190000004103325
    # http://www.jianshu.com/p/8c0fe1240e78
    #custom_font = mpl.font_manager.FontProperties(fname='SimHei')
    #font_size = 10 # 字体大小
    #fig_size = (8, 6) # 图表大小
    mpl.rcParams['font.sans-serif'] = ['SimHei'] #用来正常显示中文标签
    mpl.rcParams['axes.unicode_minus'] = False #用来正常显示负号
    
    names = (u'process1', u'process2') # 姓名
    subjects = (u'bl-switch', u'iks', u'hmp', u"hmpcb") # 科目
    scores = ((65, 90, 75, 40), (85, 80, 90, 40)) # 成绩


    # 设置柱形图宽度
    bar_width = 0.35

    index = np.arange(len(scores[0]))



    add_labels(index, scores[0], bar_width, '#0072BC', names[0])
    add_labels(index + bar_width, scores[1], bar_width, '#ED1C24', names[1])

    # X轴标题
    plt.xticks(index + bar_width, subjects)#, fontproperties=custom_font)
    # Y轴范围
    plt.ylim(ymin = 0, ymax = 100)

    # 图表标题
    plt.title(u'调度器')#, fontproperties=custom_font)
    # 图例显示在图表下方
    plt.legend(loc='upper center', bbox_to_anchor=(0.5, -0.03), fancybox=True, ncol=5)#, prop=custom_font)

    # 图表输出到本地
    plt.show( )