#------------------------------------------
#  perf sched messaging -g $GROUP
#------------------------------------------

perf_sched_bench_clear()
{
        rm -rf $LOG_DIR
        mkdir -p $LOG_DIR
        echo -e "\n+++++++++++++++++++++"
        echo "clear $LOG_DIR"
        echo -e "+++++++++++++++++++++\n"
}

perf_sched_bench_run( )
{
        if [ $BENCH == "perf" ]; then
                perf_sched_bench_perf_run
        elif [ $BENCH == "splash" ]; then
                perf_sched_bench_splash_run
        fi
}

perf_sched_bench_perf_run( )
{
        #  写入表头信息
        echo "#bench      = $BENCH"        > $RESULT_FILE
        echo "#application= $APPLICATION"  >> $RESULT_FILE
        echo "#min_group  = $MIN_GROUP"    >> $RESULT_FILE
        echo "#max_group  = $MAX_GROUP"    >> $RESULT_FILE
        echo "#step_group = $STEP_GROUP"   >> $RESULT_FILE
        echo "#loop_num   = $LOOP"         >> $RESULT_FILE
        echo "#logdir     = $LOG_DIR"      >> $RESULT_FILE
        echo "#resultfile = $RGESULT_FILE" >> $RESULT_FILE
        for (( GROUP = $MIN_GROUP; GROUP <= $MAX_GROUP; GROUP += $STEP_GROUP ))   #  增加GROUP的值
        do
                echo "+++++++++++++++++++++"
                echo "$BENCH $APPLICATION $GROUP"
                echo "+++++++++++++++++++++"

                echo "====================="
                for (( i = 1; i <= $LOOP; i++ ))          #  每次统计循环进行NUM次以防止误差
                do

                        echo -e "GROUP : $GROUP, Test Num : $i"
                        if [ $i == 1 ]; then
                                echo -e "GROUP : $GROUP, Test Num : $i" > $LOG_DIR/$GROUP.log
                        else
                                echo -e "GROUP : $GROUP, Test Num : $i" >> $LOG_DIR/$GROUP.log
                        fi

                        if [ $APPLICATION == "messaging" ]; then
                                #perf bench sched messaging -g $GROUP
                                perf bench sched messaging -g $GROUP >> $LOG_DIR/$GROUP.log
                        elif [ $APPLICATION == "pipe" ]; then
                                #perf bench sched pipe -l $GROUP
                                perf bench sched pipe -l $GROUP >> $LOG_DIR/$GROUP.log
                        fi
                done
                echo -e "=====================\n\n"
                #python readlog.py  -f $LOG_DIR/$GROUP.log -g $GROUP -l $LOOP >>$RESULT_FILE
                python readlog.py -d $(SPLASH_APPS_BIN)RESULT  -b $APPLICATION -min $MIN_GROUP -max $MAX_GROUP -step $STEP_GROUP -l $LOOP -g $GROUP >>$RESULT_FILE
        done
}

# 运行splash基准测试程序
perf_sched_bench_splash_run( )
{
        echo "#bench      = $BENCH"        > $RESULT_FILE
        echo "#application= $APPLICATION"  >> $RESULT_FILE
        echo "#loop_num   = $LOOP"         >> $RESULT_FILE
        echo "#log_dir    = $LOG_DIR"
        echo "#log_file   = $LOG_FILE"
        echo "#result_dir = $RESULT_DIR"
        echo "#result_file= $RESULT_FILE"
        echo "+++++++++++++++++++++"
        echo "$BENCH $APPLICATION"
        echo "+++++++++++++++++++++"
        #1--  BARNES < input
        #2--  FMM < inputs/input.16384
        #3--  OCEAN
        #4--  RADIOSITY -batch
        #5--  RAYTRACE -m64 inputs/car.env
        #6--  VOLREND 1 inputs/head
        #7--  WATER-NSQUARED < input
        #8--  WATER-SPATIAL < input
        echo "====================="
        SPLASH_BIN=~/Work/GitHub/Benchmark/splash-2/splash2/codes
        SPLASH_APPS_BIN=$SPLASH_BIN/apps
        SPLASH_KERNELS_BIN=$SPLASH_BIN/kernels

        LOG_FILE=$LOG_DIR/$LOOP.log
        for (( i = 1; i <= $LOOP; i++ ))          #  每次统计循环进行NUM次以防止误差
        do
                echo -e "Test Num : $i"
                echo -e "Test Num : $i" >>$LOG_FILE
                if   [ $APPLICATION == "barnes" ]; then
                        cd $SPLASH_APPS_BIN/barnes
                        ./BARNES < input >> $LOG_FILE
                elif [ $APPLICATION == "fmm" ]; then
                        cd $SPLASH_APPS_BIN/fmm
                        ./FMM < inputs/input.16384 >> $LOG_FILE
                elif [ $APPLICATION == "ocean" ]; then
                        cd $SPLASH_APPS_BIN/ocean
                        ./OCEAN >> $LOG_FILE
                elif [ $APPLICATION == "radiosity" ]; then
                        cd $SPLASH_APPS_BIN/radiosity
                        ./RADIOSITY -batch >> $LOG_FILE
                elif [ $APPLICATION == "raytrace" ]; then #5--  RAYTRACE -m64 inputs/car.env
                        cd $SPLASH_APPS_BIN/raytrace
                        ./RAYTRACE -m64 inputs/car.env >> $LOG_FILE
                elif [ $APPLICATION == "volrend" ]; then
                        $SPLASH_APPS_BIN/volrend/VOLREND 1 $SPLASH_APPS_BIN/volrend/inputs/head >> $LOG_FILE
                elif [ $APPLICATION == "water-nsquared" ]; then
                        cd $SPLASH_APPS_BIN/water-nsquared
                        ./WATER-NSQUARED < input >> $LOG_FILE
                elif [ $APPLICATION == "water-spatial" ]; then
                        cd $SPLASH_APPS_BIN/water-spatial
                        ./WATER-SPATIAL < input >> $LOG_FILE
                elif [ $APPLICATION == "cholesky" ]; then
                        cd $SPLASH_KERNELS_BIN/cholesky
                        ./CHOLESKY < inputs/lshp.O >> $LOG_FILE
                elif [ $APPLICATION == "fft" ]; then
                        cd $SPLASH_KERNELS_BIN/fft
                        ./FFT >> $LOG_FILE
                elif [ $APPLICATION == "lu" ]; then
                        cd $SPLASH_KERNELS_BIN/lu
                        ./LU >> $LOG_FILE
                elif [ $APPLICATION == "radix" ]; then
                        cd $SPLASH_KERNELS_BIN/radix >> $LOG_FILE
                        ./RADIX >> $LOG_FILE
                fi
        done

        echo "====================="
}


raw_input( )
{
        while true;
        do
                stty -icanon min 0 time 100
                echo -n "Use default to run ? (y/n) :"
                read Arg
                case $Arg in

                        Y|y|YES|yes)
                        break;;

                        N|n|NO|no)
                        exit;;

                        "")  #Autocontinue
                        break;;
                esac
        done

        echo
}


kill_perf()
{
        #########################################################################
        # File Name: kill.sh
        # Author: GatieMe
        # mail: gatieme@163.com
        # Created Time: Thu 27 Oct 2016 01:02:30 PM CST
        #########################################################################
        #!/bin/bash


        all=`pidof perf`
        all=`ps -eo pid,comm`
        for process in $all
        do
            echo $process
            kill $process
        done


}




echo $#
APPLICATION="messaging"
MIN_GROUP=1
MAX_GROUP=100
STEP_GROUP=1
LOOP=1
LOG_DIR=""
LOG_FILE=""
RESULT=""
RESULT_FILE=""
RESULT_DIR=""
LOG_DIR=""
RESULT_FILE=""

if [ $# == 7 ]; then
        echo "$0 result_dir perf app min_group max_group step_group loop"
        echo "$0 result_dir splash app loop"
        RESULT=$1
        BENCH=$2
        APPLICATION=$3
        MIN_GROUP=$4
        MAX_GROUP=$5
        STEP_GROUP=$6
        LOOP=$7
        RESULT_DIR=$RESULT/$BENCH
        LOG_DIR=$RESULT_DIR/$APPLICATION/$MIN_GROUP-$MAX_GROUP-$STEP_GROUP-$LOOP
        RESULT_FILE=$RESULT_DIR/$APPLICATION/$MIN_GROUP-$MAX_GROUP-$STEP_GROUP-$LOOP.log
elif [ $# == 4 ]; then
        RESULT=$1
        BENCH=$2
        APPLICATION=$3
        LOOP=$4
        RESULT_DIR=$RESULT/$BENCH
        LOG_DIR=$PWD/$RESULT_DIR/$APPLICATION/$LOOP
        LOG_FILE=$LOG_DIR/$LOOP.log
        RESULT_FILE=$RESULT_DIR/$APPLICATION/$LOOP.log
else
        echo "Usage :"
        echo -e "\t$0 perf [messageing|pipe] [min_group] max_group [step_group] loop"
        echo -e "\t$0 splash [barnes|fmm|ocean|radiosity|raytrace|volrend|water-nsquared |water-spatial] loop"
        echo -e "\tmessage      : use perf bench messaging -g max_group"
        echo -e "\tpipe         : use perf bench pipe -l max_group"
        echo -e "\tmax_group    : see group@messaging loop@pipe"
        echo -e "\tloop         : loop to reduces system error "
        echo -e "\t$0 $APPLICATION min_group=1 max_group=100 step_group=1 loop=1"
        #raw_input
        #APPLICATION="messaging"
        #MAX_GROUP=100
        #LOOP=1
        exit
fi


perf_sched_bench_clear
perf_sched_bench_run
