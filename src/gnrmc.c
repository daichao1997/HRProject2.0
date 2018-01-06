/*
	Extract GNRMC in raw GPS data.
	Usage: ./gnrmc <infile> <outfile>
*/

#include "csapp.h"
#include <assert.h>

int main(int argc, char *argv[]) {
	assert(argc == 3);

	FILE *infp, *outfp;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	infp = fopen(argv[1], "r");
	outfp = fopen(argv[2], "w+");

	assert(infp && outfp);

	while((read = getline(&line, &len, infp)) != EOF) {
		if(strncmp("$GNRMC", line, 6))
			continue;
		fprintf(outfp, "%s", line);
		fflush(outfp);
	}
	return 0;
}