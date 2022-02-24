

To build our code, run:

```
	g++ -std=c++11 *.cpp -o greedy -DIL_STD -fopenmp -g
	g++ -std=c++11 *.cpp -o main
```

After building, to run our code, run:

```
	./main -Alg=<algorithm, 1: kCenter 2: kMedian> 
		-data=<type, 0: Hamsterster n=2426, 1: Facebook n=4039, 2: WikiVote n=7115, 3: CaHepTh n=9877, 4: CaHepPh n=12008, 5: CaAstroPh n=18772, 6: NYroad n=264346>
		-n=<number of nodes> 
		-k=<number of nodes choosed> 
		-md=<0: original dataset, 1: shortest distance dataset>
```

Example:

```
kCenter:
	nohup ./main -alg=1 -n=2643 -data=1 -k=50 -eps=0.5 > h1.txt 2>&1 &
	nohup ./main -alg=1 -n=2643 -data=1 -k=50 -eps=1.0 > h1.txt 2>&1 &
	nohup ./main -alg=1 -n=2643 -data=1 -k=50 -eps=1.5 > h1.txt 2>&1 &
	nohup ./main -alg=1 -n=2643 -data=1 -k=50 -eps=2.0 > h1.txt 2>&1 &
	nohup ./main -alg=1 -n=2643 -data=1 -k=50 -eps=2.5 > h1.txt 2>&1 &
	nohup ./main -alg=1 -n=2643 -data=1 -k=50 -eps=3.0 > h1.txt 2>&1 &
	nohup ./main -alg=1 -data=1 -md=0 -k=20 -eps=1.0 > h1.txt 2>&1 &
	nohup ./main -alg=1 -data=2 -md=0 -k=20 -eps=1.0 > h1.txt 2>&1 &
	
kMedian:
	nohup ./main -alg=2 -n=2643 -data=1 -k=50 -eps=0.5 > h2.txt 2>&1 &
	nohup ./main -alg=2 -n=2643 -data=1 -k=50 -eps=1.0 > h2.txt 2>&1 &
	nohup ./main -alg=2 -n=2643 -data=1 -k=50 -eps=1.5 > h2.txt 2>&1 &
	nohup ./main -alg=2 -n=2643 -data=1 -k=50 -eps=2.0 > h2.txt 2>&1 &
	nohup ./main -alg=2 -n=2643 -data=1 -k=50 -eps=2.5 > h2.txt 2>&1 &
	nohup ./main -alg=2 -n=2643 -data=1 -k=50 -eps=3.0 > h2.txt 2>&1 &
	nohup ./main -alg=2 -data=1 -md=0 -k=50 -eps=1.0 > h2.txt 2>&1 &
	nohup ./main -alg=2 -data=3 -md=0 -k=20 -eps=1.0 > h2.txt 2>&1 &

	
	
	nohup ./main2 -alg=1 -data=2 -md=0 -k=20 -eps=1.0 > h1.txt 2>&1 &
	nohup ./main3 -alg=1 -data=3 -md=0 -k=20 -eps=1.0 > h1.txt 2>&1 &
	nohup ./main4 -alg=1 -data=4 -md=0 -k=20 -eps=1.0 > h1.txt 2>&1 &
	nohup ./main5 -alg=1 -data=5 -md=0 -k=20 -eps=1.0 > h1.txt 2>&1 &
```



报错处理：ulimit -c unlimited

gdb ./main core

bt

查找进程：ps -ef | grep stream

Linux下txt文件中出现^M，先vi打开，再输入 :%s/\r//g 替换