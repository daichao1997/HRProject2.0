all: gnrmc interval kernlog

gnrmc: gnrmc.c
	gcc gnrmc.c -o ../bin/gnrmc

interval: interval.cpp unpcap.h
	g++ interval.cpp -o ../bin/interval -lpcap
	
kernlog: kernlog.c
	gcc kernlog.c -o ../bin/kernlog

clean:
	rm ../bin/*.o