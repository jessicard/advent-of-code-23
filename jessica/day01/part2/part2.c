#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "usage: %s <input_file>\n", argv[0]);
        exit(1);
    }

    char *filename = argv[1];
    FILE *fp = fopen(filename, "rb");

    if (fp == NULL) {
        perror(filename);
        exit(1);
    }

    char buf[1000] = { 0 };
    int tot = 0;

    while (fgets(buf, sizeof(buf), fp) != NULL)
    {
        fprintf(stderr, "%s\n", buf);
    }

    return 0;
}
