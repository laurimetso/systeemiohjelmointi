#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 10 // määritetään rivien määrä, tää muuttuu vielä


int main(int argc, char *argv[]) {
    FILE *input_file = NULL; // tiedosto josta luetaan
    FILE *output_file = NULL; // tiedosto johon kirjoitetaan
    char *line = NULL; // pointteri stringeille
    size_t len = 0; // getline tarvitsee tämän
    char **lines = NULL; // null pointteri array mihin lisätään rivien pointterit
    int line_count = 0;
    int capacity = INITIAL_SIZE;


    if (argc > 3) {
        fprintf(stderr, "usage: reverse  <input> <output>\n");
        exit(1);
    }


    // jos ei anneta filejä (argumentteja) niin luetaan stdin ja kirjoitetaan stdout 
    if (argc == 1) {
        input_file = stdin;
        output_file = stdout;
    }
    
    // jos annetaan input file niin luetaan se ja kirjoitetaan stdout
    else if (argc == 2) {
        input_file = fopen(argv[1], "r");
        if (!input_file) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
            exit(1);
        }
        output_file = stdout;
    }
    // jos annetaan input ja output file niin luetaan input file ja kirjoitetaan output fileen.
    else if (argc == 3) {
        if (strcmp(argv[1], argv[2]) == 0) {
            fprintf(stderr, "Input and output file must differ\n");
            exit(1);
        }
        input_file = fopen(argv[1], "r");
        if (!input_file) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
            exit(1);
        }
        output_file = fopen(argv[2], "w");
        if (!output_file) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[2]);
            exit(1);
        }
    }

    //  varataan muistia riveille
    lines = malloc(capacity * sizeof(char *));
    if (!lines) {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }

    // luetaan rivit
    while ((getline(&line, &len, input_file)) != -1) {
        // lisätään muistia jos loppuu kesken
        if (line_count >= capacity) {
            capacity *= 2;
            lines = realloc(lines, capacity * sizeof(char *));
            if (!lines) {
                fprintf(stderr, "malloc failed\n");
                exit(1);
            }
        }
        

        lines[line_count++] = strdup(line);  // säilötään rivi strdupilla
    }



    // tulostetaan rivit käänteisessä järjestyksessä
    for (int i = line_count - 1; i >= 0; i--) {
        fprintf(output_file, "%s", lines[i]);
        free(lines[i]);  // vapautetaan rivi tulostuksen jälkeen
    }

    // siivotaan
    free(line);  // vapautetaan getlinen bufferi
    free(lines); // vapautetaan line pointter array

    // suljetaan mahdolliset tiedostot
    if (input_file != stdin) fclose(input_file);
    if (output_file != stdout) fclose(output_file);

    return 0;
}
