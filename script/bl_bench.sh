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
#  写入表头信息
echo "#perf_bench = $BENCH"       > $RESULT_FILE
echo "#min_group  = $MIN_GROUP"   >> $RESULT_FILE
echo "#max_group  = $MAX_GROUP"   >> $RESULT_FILE
echo "#step_group = $STEP_GROUP"  >> $RESULT_FILE
echo "#loop_num   = $LOOP"        >> $RESULT_FILE
echo "#logdir     = $LOG_DIR"     >> $RESULT_FILE
echo "#resultfile = $RESULT_FILE" >> $RESULT_FILE
for (( GROUP = $MIN_GROUP; GROUP <= $MAX_GROUP; GROUP += $STEP_GROUP ))   #  增加GROUP的值
do
        echo "+++++++++++++++++++++"
        echo "$BENCH $GROUP"
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
                if [ $BENCH == "messaging" ]; then
                        #perf bench sched messaging -g $GROUP
                        perf bench sched messaging -g $GROUP >> $LOG_DIR/$GROUP.log
                elif [ $BENCH == "pipe" ]; then
                        #perf bench sched pipe -l $GROUP
                        perf bench sched pipe -l $GROUP >> $LOG_DIR/$GROUP.log
                fi
        done
        echo -e "=====================\n\n"
        python readlog.py  -f $LOG_DIR/$GROUP.log -g $GROUP -l $LOOP >>$RESULT_FILE

done
}


raw_input()
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



RESULT_DIR=RESULT/perf

echo $#
BENCH="messaging"
MIN_GROUP=1
MAX_GROUP=100
STEP_GROUP=1
LOOP=1
LOG_DIR=""
RESULT_FILE=""

if [ $# == 0 ]; then
        echo "Usage :"
        echo -e "\t$0 [messageing|pipe] [min_group] max_group [step_group] loop"
        echo -e "\tmessage      : use perf bench messaging -g max_group"
        echo -e "\tpipe         : use perf bench pipe -l max_group"
        echo -e "\tmax_group    : see group@messaging loop@pipe"
        echo -e "\tloop         : loop to reduces system error "
        echo -e "\t$0 $BENCH min_group=1 max_group=100 step_group=1 loop=1"
        raw_input
        #BENCH="messaging"
        #MAX_GROUP=100
        #LOOP=1
elif [ $# == 1 ]; then
        echo "$0 bench min_group=1 max_group=100 step_group=1 loop=1"
        BENCH=$1
        #MAX_GROUP=100
elif [ $# == 2 ]; then
        echo "$0 bench min_group=1 max_group step_group=1 loop=1"
        BENC=$1
        MAX_GROUP=$2
elif [ $# == 3 ]; then
        echo "$0 bench min_group=1 max_group step_group=1 loop"
        BENCH=$1
        MAX_GROUP=$2
        LOOP=$3
elif [ $# == 5 ]; then
        echo "$0 bench min_group max_group step_group loop"
        BENCH=$1
        MIN_GROUP=$2
        MAX_GROUP=$3
        STEP_GROUP=$4
        LOOP=$5
fi

LOG_DIR=$RESULT_DIR/$BENCH/$MIN_GROUP-$MAX_GROUP-$STEP_GROUP-$LOOP
RESULT_FILE=$RESULT_DIR/$BENCH/$MIN_GROUP-$MAX_GROUP-$STEP_GROUP-$LOOP.log

echo "bench      = $BENCH"
echo "min_group  = $MIN_GROUP"
echo "max_group  = $MAX_GROUP"
echo "step_group = $STEP_GROUP"
echo "loop       = $LOOP"
echo "logdir     = $LOG_DIR"
echo "resultfile = $RESULT_FILE"
sleep 1


perf_sched_bench_clear
perf_sched_bench_run

