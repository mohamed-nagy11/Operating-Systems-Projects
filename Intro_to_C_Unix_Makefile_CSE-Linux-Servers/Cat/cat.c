#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Error: number of arguments is less than exprcted");
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        if (file == NULL) {
            printf("Error in opening file: %s\n", argv[i]);
            return 1;
        }

        printf("Contents of %s:\n", argv[i]);
        char ch;
        while ((ch = fgetc(file)) != EOF) {
            putchar(ch);
        }

        fclose(file);
        printf("\n");
    }

    return 0;
}