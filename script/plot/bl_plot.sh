#------------------------------------------
#  perf sched messaging -g $GROUP
#------------------------------------------


bench_plot_run()
{
	if [ $BENCH == "splash" ]; then
		splash_bench_plot_run
	elif [ $BENCH == "messaging" ] || [ $BENCH == "pipe" ]; then
		perf_bench_plot_run
	fi
}

perf_bench_plot_run( )
{
        #  写入表头信息
        echo "#directory  = $DIRECTORY"
        echo "#bench      = $BENCH"
        echo "#min_group  = $MIN_GROUP"
        echo "#max_group  = $MAX_GROUP"
        echo "#step_group = $STEP_GROUP"
        echo "#loop_num   = $LOOP"
        #echo "#logdir     = $LOG_DIR"
        python perflogplot.py -d $DIRECTORY -b $BENCH -min $MIN_GROUP -max $MAX_GROUP -step $STEP_GROUP -l $LOOP

}

splash_bench_plot_run()
{
        #  写入表头信息
        echo "#directory  = $DIRECTORY"
        echo "#bench      = $BENCH"
        echo "#loop_num   = $LOOP"
        python splashlogplot.py -d $DIRECTORY -b $BENCH -l $LOOP
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
DIRECTORY="../bench"
BENCH="messaging"
MIN_GROUP=1
MAX_GROUP=100
STEP_GROUP=1
LOOP=1
LOG_DIR=""
#RESULT_FILE=""

if [ $# == 6 ]; then
        echo "$0 directory bench=[messaging|pipe] min_group max_group step_group loop"
        DIRECTORY=$1
	BENCH=$2
        MIN_GROUP=$3
        MAX_GROUP=$4
        STEP_GROUP=$5
	LOOP=$6
elif [ $# == 3 ]; then
        echo "$0 directory bench=splash loop"
	DIRECTORY=$1
	BENCH=$2
	LOOP=$3
elif [ $# == 0 ]; then
        echo "Usage :"
        echo -e "\t$0 [messageing|pipe] [min_group] max_group [step_group] loop"
        echo -e "\tmessage      : use perf bench messaging -g max_group"
        echo -e "\tpipe         : use perf bench pipe -l max_group"
        echo -e "\tmax_group    : see group@messaging loop@pipe"
        echo -e "\tloop         : loop to reduces system error "
        echo -e "\t$0 $BENCH min_group=1 max_group=100 step_group=1 loop=1"
        #raw_input
fi

#LOG_DIR=$RESULT_DIR/$BENCH/$MIN_GROUP-$MAX_GROUP-$STEP_GROUP-$LOOP
#RESULT_FILE=$RESULT_DIR/$BENCH/$MIN_GROUP-$MAX_GROUP-$STEP_GROUP-$LOOP.log

bench_plot_run

