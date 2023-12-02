#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_calibration_value(char * line);
int is_num(char c);

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

    // Read the file line-by-line
    char line[1024]; // Assume max line length of 1024 characters
    int current = 0;
    int total = 0;
    while (fgets(line, sizeof(line), file)) {
        // Assume last character is a newline
        line[strlen(line) - 1] = 0;
        current = get_calibration_value(line);
        total += current;
        printf("%s = %d\n", line, current);
    }

    fclose(file);
    printf("total: %d\n", total);
    return 0;
}

int get_calibration_value(char * line) {
    char num[3] = { 0 };

    for (int i = 0; i < strlen(line); i++) {
        if (is_num(line[i])) {
            num[0] = line[i];
            break;
        }
    }

    for (int i = strlen(line) - 1; i >= 0; i--) {
        if (is_num(line[i])) {
            num[1] = line[i];
            break;
        }
    }

    return atoi(num);
}

int is_num(char c) {
    return c >= '0' && c <= '9';
}
