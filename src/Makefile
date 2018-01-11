all: gnrmc interval kernlog ltedbg

gnrmc: gnrmc.cpp
	g++ gnrmc.cpp -o ../bin/gnrmc -std=gnu++11

interval: interval.cpp unpcap.h
	g++ interval.cpp -o ../bin/interval -lpcap
	
kernlog: kernlog.c
	gcc kernlog.c -o ../bin/kernlog

ltedbg: ltedbg.c
	gcc ltedbg.c -o ../bin/ltedbg

clean:
	rm ../bin/*.o