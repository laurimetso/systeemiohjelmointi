
/*
	my-grep.c
	simple grep utility
	prints lines containing the search term
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
	reads lines from a file stream and prints
	lines containing the search term

*/
void grep_file(char *searchterm, FILE *fp)
{
	char *line = NULL;
	size_t len = 0;
	// read file line by line
	while (getline(&line, &len, fp) != -1) {

	// print if matches
	if (strstr(line, searchterm) != NULL) {
		printf("%s", line);
	}
	}
	free(line);
}

int main(int argc, char *argv[])
{
	// must provide search term
	if (argc < 2) {
	printf("my-grep: searchterm [file ...]\n");
	exit(1);
}

char *searchterm = argv[1];

// no file provided: read from standard input
	if (argc == 2) {
	grep_file(searchterm, stdin);
	return 0;
	}

	// process files
	for (int i = 2; i < argc; i++) {

	FILE *fp = fopen(argv[i], "r");

	// exit if file cant be opened
	if (fp == NULL) {
		printf("my-grep: cannot open file\n");
		exit(1);
	}

	grep_file(searchterm, fp);

	fclose(fp);
	}

	return 0;
}
