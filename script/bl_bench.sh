#------------------------------------------
#  perf sched messaging -g $GROUP
#------------------------------------------

RESULT_DIR=RESULT/perf

echo $#
BENCH="messaging"
MAX_GROUP=100
NUM=1


if [ $# == 0 ]; then
        echo "use default"
        #BENCH="messaging"
        #MAX_GROUP=100
        #NUM=1
elif [ $# == 1 ]; then
        BENCH=$1
        #MAX_GROUP=100
elif [ $# == 2 ]; then
        BENC=$1
        MAX_GROUP=$2
elif [ $# == 3 ]; then
        BENCH=$1
        MAX_GROUP=$2
        NUM=$3
fi

echo "bench = $BENCH"
echo "group = $MAX_GROUP"
echo "num   = $NUM"
sleep 1

mkdir -p $RESULT_DIR
mkdir -p $RESULT_DIR/$BENCH

echo "#messaging $GROUP " >> $RESULT_DIR/$BENCH/$BENCH.log
for (( GROUP = 1; GROUP <= $MAX_GROUP; GROUP ++ ))   #  增加GROUP的值
do
        echo "+++++++++++++++++++++"
        echo "#messaging $GROUP"
        echo "+++++++++++++++++++++"

        echo "====================="
        for (( i = 1; i <= $NUM; i++ ))          #  每次统计循环进行NUM次以防止误差
        do

                echo -e "GROUP : $GROUP, Test Num : $i"
                echo -e "GROUP : $GROUP, Test Num : $i" > $RESULT_DIR/$BENCH/$GROUP.log
                if [ $BENCH == "messaging" ]; then
                        #perf bench sched messaging -g $GROUP
                        perf bench sched messaging -g $GROUP >> $RESULT_DIR/$BENCH/$GROUP.log
                elif [ $BENCH == "pipe" ]; then
                        #perf bench sched pipe -l $GROUP
                        perf bench sched pipe -l $GROUP >> $RESULT_DIR/$BENCH/$GROUP.log
                fi
        done
        echo -e "=====================\n\n"
        #python ./readlog.py -p $POS -t $TYPE -n $NUM >> $RESULT_DIR/$BENCH/$BENCH.log
done
