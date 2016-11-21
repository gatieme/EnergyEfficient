
*   version

```cpp
cpufrequtils-008
```

*   how to get

```cpp
sudo apt-get -d source "cpufrequtils"
```


*   kernel tools
The cpufrequtils package (homepage:
http://www.kernel.org/pub/linux/utils/kernel/cpufreq/cpufrequtils.html )
consists of the following elements:

*   ubuntu package

cpufrequtils    :   http://packages.ubuntu.com/trusty/cpufrequtils

libcpufreq-dev  :   http://packages.ubuntu.com/trusty/libcpufreq-dev

libcpufreq0     :   http://packages.ubuntu.com/trusty/libcpufreq0


#1   libcpufreq
----------

"libcpufreq" is a library which offers a unified access method for userspace
tools and programs to the cpufreq core and drivers in the Linux kernel. This
allows for code reduction in userspace tools, a clean implementation of
the interaction to the cpufreq core, and support for both the sysfs and proc
interfaces [depending on configuration, see below].


#2  utils
-----

"cpufreq-info" determines current cpufreq settings, and provides useful
debug information to users and bug-hunters.
"cpufreq-set" allows to set a specific frequency and/or new cpufreq policies
without having to type "/sys/devices/system/cpu/cpu0/cpufreq" all the time.


#3  debug
-----

A few debug tools helpful for cpufreq have been merged into this package,
but as they are highly architecture specific they are not built by default.


#4  compilation and installation
----------------------------

make
su
make install

should suffice on most systems. It builds default libcpufreq,
cpufreq-set and cpufreq-info files and installs them in /usr/lib and
/usr/bin, respectively. If you want to set up the paths differently and/or
want to configure the package to your specific needs, you need to open
"Makefile" with an editor of your choice and edit the block marked
CONFIGURATION.


#5  THANKS
------
Many thanks to Mattia Dongili who wrote the autotoolization and
libtoolization, the manpages and the italian language file for cpufrequtils;
to Dave Jones for his feedback and his dump_psb tool; to Bruno Ducrot for his
powernow-k8-decode and intel_gsic tools as well as the french language file;
and to various others commenting on the previous (pre-)releases of
cpufrequtils.


        Dominik Brodowski
