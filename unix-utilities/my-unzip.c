/*
	creates normal text into a file from a run-length encoded file.
*/

#include <stdio.h>
#include <stdlib.h>

void unzip_file(FILE *fp)
{
    int count;
    char c;

    // read 5-byte entries: 4-byte int + 1-byte char
    while (fread(&count, 4, 1, fp) == 1) {
        if (fread(&c, 1, 1, fp) != 1) {
            break;  // malformed file
        }
        // print character count times
        for (int i = 0; i < count; i++) {
            printf("%c", c);
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("my-unzip: file1 [file2 ...]\n");
        exit(1);
    }

    // process each file
    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "rb");  // binary mode
        if (fp == NULL) {
            printf("my-unzip: cannot open file\n");
            exit(1);
        }
        unzip_file(fp);
        fclose(fp);
    }

    return 0;
}
