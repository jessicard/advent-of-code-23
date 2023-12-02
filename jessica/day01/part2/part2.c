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
    char ln[1000] = { 0 };
    int tot = 0;

    while (fgets(buf, sizeof(buf), fp) != NULL)
    {
        char num[1000] = { '\0' };
        memset(ln, 0, sizeof(ln));

        for (int i = 0; i < strlen(buf); i++)
        {
            // fprintf(stderr, "\n%lu\n", strlen(ln));
            ln[strlen(ln)] = buf[i];

            if (strstr(ln, "one") != NULL)
            {
                sprintf(&num[strlen(num)], "%c", '1');
                //fprintf(stderr, "%s", "\none\n");
                memset(ln, 0, sizeof(ln));
                continue;
            }
            if (strstr(ln, "two") != NULL)
            {
                sprintf(&num[strlen(num)], "%c", '2');
                // fprintf(stderr, "%s", "\ntwo\n");
                memset(ln, 0, sizeof(ln));
                continue;
            }
            if (strstr(ln, "three") != NULL)
            {
                sprintf(&num[strlen(num)], "%c", '3');
                // fprintf(stderr, "%s", "\nthree\n");
                memset(ln, 0, sizeof(ln));
                continue;
            }
            if (strstr(ln, "four") != NULL)
            {
                sprintf(&num[strlen(num)], "%c", '4');
                // fprintf(stderr, "%s", "\nfour\n");
                memset(ln, 0, sizeof(ln));
                continue;
            }
            if (strstr(ln, "five") != NULL)
            {
                sprintf(&num[strlen(num)], "%c", '5');
                // fprintf(stderr, "%s", "\nfive\n");
                memset(ln, 0, sizeof(ln));
                continue;
            }
            if (strstr(ln, "six") != NULL)
            {
                sprintf(&num[strlen(num)], "%c", '6');
                // fprintf(stderr, "%s", "\nsix\n");
                memset(ln, 0, sizeof(ln));
                continue;
            }
            if (strstr(ln, "seven") != NULL)
            {
                sprintf(&num[strlen(num)], "%c", '7');
                // fprintf(stderr, "%s", "\nseven\n");
                memset(ln, 0, sizeof(ln));
                continue;
            }
            if (strstr(ln, "eight") != NULL)
            {
                sprintf(&num[strlen(num)], "%c", '8');
                // fprintf(stderr, "%s", "\neight\n");
                memset(ln, 0, sizeof(ln));
                continue;
            }
            if (strstr(ln, "nine") != NULL)
            {
                sprintf(&num[strlen(num)], "%c", '9');
                // fprintf(stderr, "%s", "\nnine\n");
                memset(ln, 0, sizeof(ln));
                continue;
            }

            // fprintf(stderr, "%c", ln[i]);

            if (isdigit(buf[i]))
            {
                // fprintf(stderr, "%c", buf[i]);
                sprintf(&num[strlen(num)], "%c", buf[i]);
                memset(ln, 0, sizeof(ln));
            }

        }

        num[1] = num[strlen(num) - 1];
        num[2] = '\0';

        fprintf(stderr, "%d\n", j);

        tot += atoi(num);
    }

    fprintf(stderr, "%d", tot);

    return 0;
}
