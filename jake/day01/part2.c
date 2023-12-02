#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_calibration_value(char * line);
int is_num(char c);
char * get_first_spelled_ptr(char *line);
char * get_last_spelled_ptr(char *original);
char parse_spelled(char *str);
int starts_with(char *haystack, char *needle);
char *strrev(char *str);

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

    int current = 0;
    int total = 0;

    // Read the file line-by-line
    char line[1024]; // Assume max line length of 1024 characters
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
    char *first_digit_ptr = NULL;
    char *last_digit_ptr = NULL;
    char *first_spelled_ptr = NULL;
    char *last_spelled_ptr = NULL;

    char *curr_char_ptr = line;

    // Get the location of the first digit.
    while (*curr_char_ptr != 0) {
        if (is_num(*curr_char_ptr)) {
            first_digit_ptr = curr_char_ptr;
            break;
        }

        curr_char_ptr++;
    }

    // Move to end of string.
    curr_char_ptr = line + strlen(line) - 1;

    // Get the location of the last digit.
    while (curr_char_ptr >= line) {
        if (is_num(*curr_char_ptr)) {
            last_digit_ptr = curr_char_ptr;
            break;
        }

        curr_char_ptr--;
    }

    first_spelled_ptr = get_first_spelled_ptr(line);
    last_spelled_ptr = get_last_spelled_ptr(line);

    if (first_spelled_ptr && first_spelled_ptr < first_digit_ptr) {
        num[0] = parse_spelled(first_spelled_ptr);
    } else if (first_digit_ptr) {
        num[0] = *first_digit_ptr;
    } else {
        fprintf(stderr, "Both pointers null\n");
    }

    if (last_spelled_ptr && last_spelled_ptr > last_digit_ptr) {
        num[1] = parse_spelled(last_spelled_ptr);
    } else if (last_digit_ptr) {
        num[1] = *last_digit_ptr;
    } else {
        fprintf(stderr, "Both pointers null\n");
    }

    return atoi(num);
}

int is_num(char c) {
    return c >= '0' && c <= '9';
}

char * get_first_spelled_ptr(char *line) {
    // abcone2threexyz
    //    ^
    // should return that pointer
    char *lowest = NULL;
    char *ptrs[10];
    ptrs[0] = strstr(line, "zero");
    ptrs[1] = strstr(line, "one");
    ptrs[2] = strstr(line, "two");
    ptrs[3] = strstr(line, "three");
    ptrs[4] = strstr(line, "four");
    ptrs[5] = strstr(line, "five");
    ptrs[6] = strstr(line, "six");
    ptrs[7] = strstr(line, "seven");
    ptrs[8] = strstr(line, "eight");
    ptrs[9] = strstr(line, "nine");

    for (int i = 0; i < 10; i++) {
        if (ptrs[i] && (ptrs[i] < lowest || !lowest)) {
            lowest = ptrs[i];
        }
    }

    return lowest;
}

char * get_last_spelled_ptr(char *original) {
    // abcone2threexyz
    //        ^
    // should return that pointer
    char rev_line[1024] = { 0 }; // Assume max line length of 1024 characters
    size_t len = strlen(original);
    strncpy(rev_line, original, len);
    strrev(rev_line);

    char *lowest = NULL;
    char *ptrs[10];

    // initially will find this pointer:
    // zyxeerht2enocba
    //    ^
    // We add offsets to push it up. In this case:
    // zyxeerht2enocba
    //        ^
    ptrs[0] = strstr(rev_line, "orez");
    if (ptrs[0]) ptrs[0] += 3;
    ptrs[1] = strstr(rev_line, "eno");
    if (ptrs[1]) ptrs[1] += 2;
    ptrs[2] = strstr(rev_line, "owt");
    if (ptrs[2]) ptrs[2] += 2;
    ptrs[3] = strstr(rev_line, "eerht");
    if (ptrs[3]) ptrs[3] += 4;
    ptrs[4] = strstr(rev_line, "ruof");
    if (ptrs[4]) ptrs[4] += 3;
    ptrs[5] = strstr(rev_line, "evif");
    if (ptrs[5]) ptrs[5] += 3;
    ptrs[6] = strstr(rev_line, "xis");
    if (ptrs[6]) ptrs[6] += 2;
    ptrs[7] = strstr(rev_line, "neves");
    if (ptrs[7]) ptrs[7] += 4;
    ptrs[8] = strstr(rev_line, "thgie");
    if (ptrs[8]) ptrs[8] += 4;
    ptrs[9] = strstr(rev_line, "enin");
    if (ptrs[9]) ptrs[9] += 3;

    for (int i = 0; i < 10; i++) {
        if (ptrs[i] != NULL && (ptrs[i] < lowest || !lowest)) {
            lowest = ptrs[i];
        }
    }

    if (!lowest) return NULL;
    // zyxeerht2enocba
    //        ^
    // ^
    // = 7
    int distance_from_end_of_original = lowest - rev_line;

    //              abcone2threexyz
    // original:    ^
    //              abcone2threexyz
    // + (len - 1):               ^
    //              abcone2threexyz
    // - 7:                ^
    return original + (len - 1) - distance_from_end_of_original;
}

char parse_spelled(char *str) {
    if (starts_with(str, "zero")) {
        return '0';
    } else if (starts_with(str, "one")) {
        return '1';
    } else if (starts_with(str, "two")) {
        return '2';
    } else if (starts_with(str, "three")) {
        return '3';
    } else if (starts_with(str, "four")) {
        return '4';
    } else if (starts_with(str, "five")) {
        return '5';
    } else if (starts_with(str, "six")) {
        return '6';
    } else if (starts_with(str, "seven")) {
        return '7';
    } else if (starts_with(str, "eight")) {
        return '8';
    } else if (starts_with(str, "nine")) {
        return '9';
    } else {
        fprintf(stderr, "Shouldn't have parsed\n");
        exit(1);
    }
}

int starts_with(char *haystack, char *needle) {
    if (!haystack) return 0;

    size_t len = strlen(needle);
    if (strlen(haystack) < len) return 0;

    return strncmp(needle, haystack, len) == 0;
}

char *strrev(char *str) {
    if (!str || !*str) return str;
    char *p1, *p2;

    for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2) {
        *p1 ^= *p2;
        *p2 ^= *p1;
        *p1 ^= *p2;
    }

    return str;
}