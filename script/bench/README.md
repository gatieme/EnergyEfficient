#!/bin/bash

#  1  sysbench
-------


##  1.1  CPU测试
-------
sysbench采用寻找最大素数的方式来测试CPU的性能

```cpp
sysbench --test=cpu --cpu-max-prime=2000 run
```


##  1.2  文件IO性能测试
-------




###  1.2.1  首先生成需要的测试文件
-------

文件总大小300M, 16个并发线程, 随机读写模式.

执行完后会在当前目录下生成一堆小文件

```cpp
sysbench --test=fileio --num-threads=16 --file-total-size=300M --file-test-mode=rndrw prepare
```

###  1.2.2  执行测试
-------

```cpp
sysbench --test=fileio --num-threads=16 --file-total-size=300M --file-test-mode=rndrw run
```

###  1.2.3  清理现场
-------

```cpp
sysbench --test=fileio --num-threads=16 --file-total-size=300M --file-test-mode=rndrw cleanup
```


##  1.3  Mutex测试
-------

```cpp
sysbench --test=mutex --num-threads=16 \--mutex-num=1024 --mutex-locks=10000 --mutex-loops=5000 run
```

##  1.4  内存测试
-------

```cpp
sysbench --test=memory --num-threads=16 --memory-block-size=8192 --memory-total-size=1G run
```


##  1.5  MySQL数据库测试
-------

###1.5.1--创建默认的sbtest数据库
-------

-首先需要创建默认的sbtest数据库, 或者使用–mysql-db指定一个已经存在的数据库生成测试数据


引擎为myisam,表大小为1000000条记录

```cpp
sysbench --test=oltp --mysql-table-engine=myisam --oltp-table-size=1000000 --mysql-user=root --mysql-socket=/opt/mysql/run/mysql.sock prepare
```

###  1.5.2  执行测试
-------


```cpp
sysbench --test=oltp --mysql-table-engine=myisam --oltp-table-size=1000000 --mysql-user=root --mysql-socket=/opt/mysql/run/mysql.sock run
```

###  1.5.3  清理现场
-------


```cpp
sysbench --test=oltp --mysql-table-engine=myisam --oltp-table-size=1000000 --mysql-user=root --mysql-socket=/opt/mysql/run/mysql.sock cleanup
```


#  2  perf bench
-------

除了调度器之外, 很多时候人们都需要衡量自己的工作对系统性能的影响.
benchmark 是衡量性能的标准方法, 对于同一个目标, 如果能够有一个大家都承认的 benchmark, 将非常有助于”提高内核性能”这项工作。

目前, 就我所知, perf bench 提供了 3 个 benchmark:


##  2.1  Sched message
-------

==**描述**==

sched message 是从经典的测试程序 hackbench 移植而来, 用来衡量调度器的性能，overhead 以及可扩展性。

该 benchmark 启动 N 个 reader/sender 进程或线程对, 通过 IPC(socket 或者 pipe) 进行并发的读写。

一般人们将 N 不断加大来衡量调度器的可扩展性。

==**用法**==

Sched message 的用法及用途和 hackbench 一样。

```cpp
perf bench sched messaging --help
```

```cpp
# Running 'sched/messaging' benchmark:

 Usage: perf bench sched messaging <options>

    -g, --group <n>       Specify number of groups (default: 20)
    -l, --nr_loops <n>    Specify the number of loops to run (default: 100)
    -p, --pipe            Use pipe() instead of socketpair()
    -t, --thread          Be multi thread instead of multi process
```


==**使用**==

```cpp
perf bench sched messaging -g N
```

```cpp
# Running sched/messaging benchmark...# 
# 20 sender and receiver processes per group
# 10 groups == 400 processes run 
#       Total time: 1.918 [sec]
```


##  2.2  Sched Pipe
-------


==**描述**==

从 Ingo Molnar 的 pipe-test-1m.c 移植而来。
当初 Ingo 的原始程序是为了测试不同的调度器的性能和公平性的。
其工作原理很简单，两个进程互相通过 pipe 拼命地发 1000000 个整数，进程 A 发给 B，同时 B 发给 A. 因为 A 和 B 互相依赖，因此假如调度器不公平，对 A 比 B 好, 那么 A 和 B 整体所需要的时间就会更长。

==**用法**==


```cpp
perf bench sched pipe --help
```


```cpp
# Running 'sched/pipe' benchmark:

 Usage: perf bench sched pipe <options>

    -l, --loop <n>        Specify number of loops
    -T, --threaded        Specify threads/process based task setup
```


==**使用**==


```cpp
perf bench sched pipe
```

```cpp
# Running 'sched/pipe' benchmark:
# Executed 1000000 pipe operations between two processes

     Total time: 7.035 [sec]

       7.035049 usecs/op
         142145 ops/sec
```


##  2.3  Mem memcpy
-------

==**描述**==


这个是 perf bench 的作者 Hitoshi Mitake 自己写的一个执行 memcpy 的 benchmark。该测试衡量一个拷贝 1M 数据的 memcpy() 函数所花费的时间。我尚不明白该 benchmark 的使用场景。。。或许是一个例子，告诉人们如何利用 perf bench 框架开发更多的 benchmark 吧.


==**用法**==

```cpp
perf bench mem memcpy --help
```

```cpp
# Running 'mem/memcpy' benchmark:

 Usage: perf bench mem memcpy <options>

    -c, --cycles          Use a cycles event instead of gettimeofday() to measure performance
    -f, --function <all>  Specify the function to run, "all" runs all available functions, "help" lists
    -l, --nr_loops <n>    Specify the number of loops to run. (default: 1)
    -s, --size <1MB>      Specify the size of the memory buffers. Available units: B, KB, MB, GB and TB
```


==**使用**==

```cpp
perf bench mem memcpy
```


```cpp
# Running 'mem/memcpy' benchmark:
# function 'default' (Default memcpy() provided by glibc)
# Copying 1MB bytes ...

       7.570252 GB/sec
# function 'x86-64-unrolled' (unrolled memcpy() in arch/x86/lib/memcpy_64.S)
# Copying 1MB bytes ...

       7.180607 GB/sec
# function 'x86-64-movsq' (movsq-based memcpy() in arch/x86/lib/memcpy_64.S)
# Copying 1MB bytes ...

       6.220143 GB/sec
# function 'x86-64-movsb' (movsb-based memcpy() in arch/x86/lib/memcpy_64.S)
# Copying 1MB bytes ...

       1.941476 GB/sec
```
