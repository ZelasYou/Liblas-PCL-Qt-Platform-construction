#include <iostream>
int numofPoints(char* fname) {
	int n = 0;
	int c = 0;
	FILE *fp;
	fp = fopen(fname, "r");
	do {
		c = fgetc(fp);
		if (c == '\n') {
			++n;
		}
	}
	while (c != EOF);
	fclose(fp);

	return n;
}