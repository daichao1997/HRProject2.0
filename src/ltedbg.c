#define _GNU_SOURCE
#include "csapp.h"
#include <assert.h>
#include <time.h>

FILE *infp, *outfp, *errfp;
char timestr[50], sig[50];
char *line, *begin, *end;
size_t len;
ssize_t r;
struct tm t;
time_t secs;
int _sig;

int main(int argc, char *argv[]) {
	assert(argc == 3);

	infp = fopen(argv[1], "r");
	outfp = fopen(argv[2], "w+");
	//errfp = fopen(argv[3], "w+");
	
	assert(infp && outfp);

	while((r = getline(&line, &len, infp)) != EOF) {
		if(strstr(line, "CTS")) {
			if(_sig < 0 && secs > 1500000000 && secs < 2000000000) {
				fprintf(outfp, "%ld,%d\n", secs, _sig);
				fflush(outfp);
			}
			memset(timestr, 0, sizeof(timestr));
			memset(sig, 0, sizeof(sig));
			memset(&t, 0, sizeof(t));
			secs = _sig = 0;

			strncpy(timestr, line, strlen("Tue Dec 19 11:26:42"));
			strcat(timestr, " 2017");
			strptime(timestr, "%a %b %d %H:%M:%S %Y", &t);
			secs = mktime(&t);
		}
		else if(strstr(line, "RSSI") && (end = strstr(line, "dbm"))) {
			begin = line + strlen("RSSI:");
			strncpy(sig, begin, end-begin);
			_sig = atoi(sig);
		}
	}
	return 0;
}