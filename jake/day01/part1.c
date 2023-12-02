#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    }

    // Open the file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }

    // Read and print the contents of the file line-by-line
    char line[1024]; // Assume max line length of 1024 characters
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
    putchar('\n');
    return 0;
}
