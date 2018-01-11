/*
	Extract GNRMC in raw GPS data.
	Usage: ./gnrmc <infile> <outfile>
*/

#include "csapp.h"
#include <assert.h>
#include <regex>
#include <string>
using namespace std;

regex e("^\\$GNRMC,[0-9]{6}\\.00,[A-Z]?,[0-9]{4}\\.[0-9]{5},[A-Z]?,[0-9]{5}\\.[0-9]{5},[A-Z]?,[0-9]+\\.[0-9]{3},.*,[0-9]{6}");
smatch sm;

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
		if(!strstr(line, "$GNRMC"))
			continue;
		string _line(line);
		if(!regex_search(_line, sm, e))
			continue;
		fprintf(outfp, "%s", line);
		fflush(outfp);
	}
	return 0;
}