
/*
	my-cat.c
	simple cat utility
	reads and prints contents of a given file
*/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	// no files are provided, exit succesfully
        if (argc == 1){
                return 0;
        }

        char buffer[4096];

	// process each file given in command-line arguments
        for (int i = 1; i<argc; i++) {

		// open file in read mode
                FILE *fp = fopen(argv[i], "r");

		// exit with error if file cant be opened
                if (fp == NULL) {
                        printf("my-cat: cannot open file\n");
                        exit(1);
                }

		// read and print file contents line by line
                while (fgets(buffer,sizeof(buffer),fp)!=NULL){
                        printf("%s",buffer);
                }

		// close file
                fclose(fp);
        }
        return(0);
}
