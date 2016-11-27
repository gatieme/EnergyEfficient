#ifndef CONFIG_H
#define CONFIG_H


//#define __DEBUG__

/// usage的基数
/// usage的值为unsigned long, 单位为hz
/// 数值范围太大不好表示, 因此/CARDINAL_NUMBER进行单位转换
#define USAGE_CARDINAL_NUMBER 1000.0  //cardinal number


#define QWT_PLOT_POINT_WIDTH    2
#define QWT_PLOT_CURVE_WIDTH    2
#endif // CONFIG_H
