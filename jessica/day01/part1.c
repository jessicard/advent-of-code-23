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
    char nums[1000] = { 0 };

    while (fgets(buf, sizeof(buf), fp) != NULL)
    {
        char num[1000] = { '\0' };
        for (int i = 0; i < strlen(buf); i++)
        {
            if (isdigit(buf[i]))
            {
                sprintf(&num[strlen(num)], "%c", buf[i]);
            }
        }
        fprintf(stderr, "%s\n", num);
        // sprintf(&nums[strlen(nums)], "%d%d", atoi(&num[0]), atoi(&num[strlen(num) - 1]));
    }

    int tot = 0;
    for (int i = 0; i < strlen(nums); i++)
    {
        tot += atoi(&nums[i]);
    }

    // fprintf(stderr, "%d", tot);

    return 0;
}
