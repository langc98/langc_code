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
		-md=<0: original dataset, 1: shortest distance dataset>
		-k=<number of nodes choosed>
		-eps=<privacy budget>
```

Example:

```
kCenter:
	nohup ./main -alg=1 -data=0 -n=2426 -md=1 -k=20 -eps=0.5 > h.txt 2>&1 &
	
	nohup ./main0 -alg=1 -data=0 -md=1 -k=20 > h1.txt 2>&1 &
	nohup ./main1 -alg=1 -data=1 -md=1 -k=20 > h1.txt 2>&1 &
	nohup ./main2 -alg=1 -data=2 -md=1 -k=20 > h1.txt 2>&1 &
	nohup ./main3 -alg=1 -data=3 -md=1 -k=20 > h1.txt 2>&1 &
	nohup ./main4 -alg=1 -data=4 -md=1 -k=20 > h1.txt 2>&1 &
	
kMedian:
	nohup ./main -alg=2 -data=0 -n=2426 -md=1 -k=20 -eps=0.5 > h.txt 2>&1 &
	
	nohup ./main0 -alg=2 -data=0 -md=1 -k=20 > h2.txt 2>&1 &
	nohup ./main1 -alg=2 -data=1 -md=1 -k=20 > h2.txt 2>&1 &
	nohup ./main2 -alg=2 -data=2 -md=1 -k=20 > h2.txt 2>&1 &
	nohup ./main3 -alg=2 -data=3 -md=1 -k=20 > h2.txt 2>&1 &
	nohup ./main4 -alg=2 -data=4 -md=1 -k=20 > h2.txt 2>&1 &
	
