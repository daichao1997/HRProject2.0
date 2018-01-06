/*
	Preprocess kernel log.
	Usage: ./kernlog <infile1> <infile2> <outfile> <errorfile>
*/
#define _GNU_SOURCE
#include "csapp.h"
#include <assert.h>
#include <time.h>

int main(int argc, char *argv[]) {
	assert(argc == 4);

	FILE *infp, *outfp, *errfp;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	infp = fopen(argv[1], "r");
	outfp = fopen(argv[2], "w+");
	errfp = fopen(argv[3], "w+");
	
	assert(infp && outfp && errfp);

	while((read = getline(&line, &len, infp)) != EOF) {
		char *tmp = strstr(line, "netdump");
		if(!tmp) {
			fprintf(errfp, "%s", line);
			fflush(errfp);
			continue;
		}
		char time[50];
		struct tm t;
		time_t secs;
		uint32_t srcip, dstip, srcport, dstport, mark;

		strncpy(time, line, strlen("Tue Dec 19 11:26:42 2017"));
		strptime(time, "%a %b %d %H:%M:%S %Y", &t);
		secs = mktime(&t);

		
		sscanf(tmp, "%*s %x %x %x %x %x\n", &srcip, &dstip, &srcport, &dstport, &mark);

		srcip = ntohl(srcip);
		dstip = ntohl(dstip);
		srcport = ntohs(srcport);
		dstport = ntohs(dstport);
		mark >>= 4;
		if(!(mark >= 1 && mark <= 9))
			continue;

		fprintf(outfp, "%ld,%08x,%08x,%d,%d,%d\n", secs, srcip, dstip, srcport, dstport, mark);
		fflush(outfp);
	}
	return 0;
}