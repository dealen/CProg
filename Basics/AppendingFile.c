#include <stdio.h>
#include <stdlib.h>

// ./AppendFile filename word1 word2 word3
int main(int argc, char *argv[]){

    printf("argc: %d\n", argc);
    if (argc < 2){
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(argv[1], "a");
    if (file == NULL) {
        printf("error with path!");
        exit(EXIT_FAILURE);
    }

    // modifying the file
    for (int i = 2; i < argc; i++) {
        fprintf(file, "%s\n", argv[i]);
    }

    fclose(file);

    printf("Text appended!\n\n");
    FILE *readFile = fopen(argv[1], "r");
    if (readFile == NULL){
        printf("error while opening file for reading!");
        exit(EXIT_FAILURE);
    }

    int ch;
    while ((ch = fgetc(readFile)) != EOF) {
        putchar(ch);
    }

    fclose(readFile);

    return 0;
}
