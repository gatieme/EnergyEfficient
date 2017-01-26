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
echo "#bench = $BENCH"          > $RESULT_FILE
echo "#group = $MAX_GROUP"      >> $RESULT_FILE
echo "#num   = $LOOP"            >> $RESULT_FILE
for (( GROUP = 1; GROUP <= $MAX_GROUP; GROUP ++ ))   #  增加GROUP的值
do
        echo "+++++++++++++++++++++"
        echo "#messaging $GROUP"
        echo "$BENCH"
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
        #python ./readlog.py -p $POS -t $TYPE -n $LOOP >> $RESULT_DIR/$BENCH.log
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



RESULT_DIR=RESULT/perf

echo $#
BENCH="messaging"
MAX_GROUP=100
LOOP=1
LOG_DIR=""
RESULT_FILE=""

if [ $# == 0 ]; then
        echo "Usage :"
        echo -e "\t$0 [messageing|pipe] max_group loop"
        echo -e "\tmessage      : use perf bench messaging -g max_group"
        echo -e "\tpipe         : use perf bench pipe -l max_group"
        echo -e "\tmax_group    : see group@messaging loop@pipe"
        echo -e "\tloop         : loop to reduces system error "
        
        raw_input
        #BENCH="messaging"
        #MAX_GROUP=100
        #LOOP=1
elif [ $# == 1 ]; then
        BENCH=$1
        #MAX_GROUP=100
elif [ $# == 2 ]; then
        BENC=$1
        MAX_GROUP=$2
elif [ $# == 3 ]; then
        BENCH=$1
        MAX_GROUP=$2
        LOOP=$3
fi

LOG_DIR=$RESULT_DIR/$BENCH/$MAX_GROUP-$LOOP
RESULT_FILE=$RESULT_DIR/$BENCH/$BENCH-$MAX_GROUP-$LOOP.log

echo "bench      = $BENCH"
echo "group      = $MAX_GROUP"
echo "num        = $LOOP"
echo "logdir     = $LOG_DIR"
echo "resultfile = $RESULT_FILE"
sleep 1


perf_sched_bench_clear
perf_sched_bench_run
