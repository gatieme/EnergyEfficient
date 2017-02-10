sh bl_bench.sh messaging 5 200 5 5
sh bl_bench.sh messaging 100 100 5 100
sh bl_bench.sh messaging 20 20 5 100
sh bl_bench.sh messaging 10 10 5 100

sh bl_bench.sh pipe 1000 10000 1000 10
sh bl_bench.sh pipe 10000 100000 10000 10
sh bl_bench.sh pipe 100000 1000000 100000 10
sh bl_bench.sh pipe 100000 100000 5 100


python readlog.py -d ./RESULT  -b $BENCH -min $MIN_GROUP -max $MAX_GROUP -step $STEP_GROUP -l $LOOP -g $GROUP >>$RESULT_FILE 
python logplot.py -d ../bench -n RESULT  -b messaging -min 10 -max 100 -step 10 -l 5
