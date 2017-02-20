#CC-A80-linux-sdk
#================

#mkdir cc-A80-linux-sdk
#cd cc-a80-linux-sdk

git clone https://github.com/cubieboard/CC-A80-kernel-source    3.4
git clone https://github.com/cubieboard/CC-A80-products         products
git clone https://github.com/cubieboard/CC-A80-tools            tools
git clone https://github.com/cubieboard/CC-A80-binaries         binaries
git clone https://github.com/cubieboard/CC-A80-rootfs.git       rootfs

#Sdk guide :/Model/CC-A80/Doc/lubuntu


#接法 : 白色接TX, 绿色接RX, 黑色接GND, 注意红色不接, 为防止误插可以剪掉


#SanDisk        刷入了hmp_proc_idle     (模拟hmpcb)
#emmc           刷入了hmp_proc_idle     (模拟hmp)
#Kingston       刷入了iks               (作对照试验, non idle)
#Team           待刷入bl-switch         (作对照实验)

#iks下, 系统关机时, 会死在wakequeue_cpu_call函数,
#iks下增加了cpu idle配置后, 系统segment fault几率增加, 并有较大概率系统无法启动
