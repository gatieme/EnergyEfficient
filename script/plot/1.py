#!/usr/bin/python
# encoding=utf-8


#!coding:utf-8
# http://www.jianshu.com/p/8c0fe1240e78
# https://segmentfault.com/a/1190000004103325
import numpy as np
import matplotlib as mpl
#mpl.use('Agg')
from matplotlib import pyplot as plt


if __name__ == '__main__':
    plt.figure(figsize=(9,6))
    n = 8
    X = np.arange(n)+1

    #X是1,2,3,4,5,6,7,8,柱的个数
    # numpy.random.uniform(low=0.0, high=1.0, size=None), normal
    #uniform均匀分布的随机数，normal是正态分布的随机数，0.5-1均匀分布的数，一共有n个
    Y1 = np.random.uniform(0.5,1.0,n)
    Y2 = np.random.uniform(0.5,1.0,n)
    plt.bar(X,Y1,width = 0.35,facecolor = 'lightskyblue',edgecolor = 'white')
    #width:柱的宽度
    plt.bar(X+0.35,Y2,width = 0.35,facecolor = 'yellowgreen',edgecolor = 'white')
    #水平柱状图plt.barh，属性中宽度width变成了高度height
    #打两组数据时用+
    #facecolor柱状图里填充的颜色
    #edgecolor是边框的颜色
    #想把一组数据打到下边，在数据前使用负号
    #plt.bar(X, -Y2, width=width, facecolor='#ff9999', edgecolor='white')
    #给图加text
    for x,y in zip(X,Y1):
        plt.text(x+0.3, y+0.05, '%.2f' % y, ha='center', va= 'bottom')

    for x,y in zip(X,Y2):
        plt.text(x+0.6, y+0.05, '%.2f' % y, ha='center', va= 'bottom')
    plt.ylim(0,+1.25)

    custom_font = mpl.font_manager.FontProperties(fname='/Library/Fonts/华文细黑.ttf')
    font_size = 10 # 字体大小
    fig_size = (8, 6) # 图表大小
    plt.legend(loc='upper center', bbox_to_anchor=(0.5, -0.03), fancybox=True, ncol=5, prop=custom_font)

    plt.show()