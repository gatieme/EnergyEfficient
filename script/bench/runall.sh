sh bl_bench.sh messaging 5 200 5 5
sh bl_bench.sh messaging 10 100 10 10
sh bl_bench.sh messaging 20 200 20 10

sh bl_bench.sh messaging 100 100 5 100
sh bl_bench.sh messaging 50 50 5 100
sh bl_bench.sh messaging 20 20 5 100
sh bl_bench.sh messaging 10 10 5 100


sh bl_bench.sh pipe 100 1000 100 10
sh bl_bench.sh pipe 1000 10000 1000 10
sh bl_bench.sh pipe 10000 100000 10000 10
sh bl_bench.sh pipe 100000 1000000 100000 10
sh bl_bench.sh pipe 1000 1000000 1000 10


sh bl_bench.sh pipe 1000 1000 5 100
sh bl_bench.sh pipe 10000 10000 5 100
sh bl_bench.sh pipe 100000 100000 5 100
sh bl_bench.sh pipe 1000000 1000000 5 100


python readlog.py -d ./RESULT  -b $BENCH -min $MIN_GROUP -max $MAX_GROUP -step $STEP_GROUP -l $LOOP -g $GROUP >>$RESULT_FILE 
python logplot.py -d ../bench -n RESULT  -b messaging -min 10 -max 100 -step 10 -l 5



#example
#bl 缺少 50-50-5-100 10-10-5-100
#hmp 缺少 50-50-5-100
#hmpcb 缺少 50-50-5-100
python logplot.py -d ../bench -b messaging -min 5 -max 200 -step 5 -l 5
python logplot.py -d ../bench -b messaging -min 10 -max 100 -step 5 -l 5
python logplot.py -d ../bench -b messaging -min 20 -max 200 -step 5 -l 5

python logplot.py -d ../bench -b messaging -min 100 -max 100 -step 5 -l 100
python logplot.py -d ../bench -b messaging -min 50 -max 50 -step 5 -l 100
python logplot.py -d ../bench -b messaging -min 20 -max 20 -step 5 -l 100
python logplot.py -d ../bench -b messaging -min 10 -max 10 -step 5 -l 100


# 缺少hmpcb
python logplot.py -d ../bench -b pipe -min 100 -max 1000 -step 100 -l 10
python logplot.py -d ../bench -b pipe -min 1000 -max 10000 -step 1000 -l 10
python logplot.py -d ../bench -b pipe -min 10000 -max 100000 -step 10000 -l 10
python logplot.py -d ../bench -b pipe -min 100000 -max 1000000 -step 100000 -l 10

python logplot.py -d ../bench -b pipe -min 10000 -max 10000 -step 5 -l 100
python logplot.py -d ../bench -b pipe -min 100000 -max 100000 -step 5 -l 100
python logplot.py -d ../bench -b pipe -min 1000000 -max 1000000 -step 5 -l 100
