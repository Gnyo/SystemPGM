#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

// main
int main(int argc, char *argv[]) {
    extern char **environ;
    char **ptr;
    int null_terminate = 0;

    const char *short_options = "0";
    static struct option long_options[] = {
        {"null", no_argument, 0, '0'},
        {0, 0, 0, 0}
    };

    int opt;
    while ((opt = getopt_long(argc, argv, short_options, long_options, NULL)) != -1) {
        switch (opt) {
            case '0':
                null_terminate = 1;
                break;
            case '?':
            default:
                fprintf(stderr, "사용 방법: %s [-0|--null]\n", argv[0]);
                return 1;
        }
    }

    // printenv with no arguments → 전체 환경 변수 출력
    for (ptr = environ; *ptr != NULL; ptr++) {
        printf("%s", *ptr);
        if (null_terminate)
            putchar('\0');
        else
            putchar('\n');
    }

    return 0;
}
