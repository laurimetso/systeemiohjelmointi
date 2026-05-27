/*
        compresses a file using run-length encoding by storing
        consecutive characters as a count and the character itself.

*/

#include <stdio.h>
#include <stdlib.h>

void zip_file(FILE *fp)
{
	int character;
	int count = 1;
	int prev = EOF;

	while ((character = fgetc(fp)) != EOF) {
	// if character changed or count would overfloww

	if (character != prev || count == 255) {
		if (prev != EOF) {
		// write the 4 byte count and the character
			fwrite(&count, 4, 1, stdout);
			fputc(prev, stdout);
		}
		prev = character;
		count = 1;
		} else {
			count++;
		}
	}
	// write the last run
	if (prev != EOF) {
		fwrite(&count, 4, 1, stdout);
		fputc(prev, stdout);
	}
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("my-zip: file1 [file2 ...] \n");
		exit(1);
	}

	// process each file
	for (int i = 1; i<argc; i++) {
		FILE *fp = fopen(argv[i], "r");
		if (fp == NULL) {
			printf("my-zip: cannot open file\n");
			exit(1);
		}
		zip_file(fp);
		fclose(fp);
	}
	return 0;
}
