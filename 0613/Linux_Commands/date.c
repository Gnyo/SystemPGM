#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 오류 출력 함수
void error_print(char *argv[]) {
    fprintf(stderr, "\033[0;31m%s: 잘못된 사용방법입니다.\033[0m\n", argv[0]);
    fprintf(stderr, "사용 방법: %s \033[0;34m[옵션]\033[0m\n", argv[0]);
}

void short_error(char *argv[], char optopt) {
    fprintf(stderr, "\033[0;31m%s: '-%c'는(은) 인식할 수 없는 옵션입니다.\033[0m\n", argv[0], optopt);
}

void long_error(char *argv[], int optind) {
    fprintf(stderr, "\033[0;31m%s: '%s'는(은) 인식할 수 없는 옵션입니다.\033[0m\n", argv[0], argv[optind - 1]);
}

int main(int argc, char *argv[]) {
    int flag_u = 0;
    int flag_r = 0;

    time_t t;
    struct tm *timeinfo;
    char buffer[128];

    const char *short_options = "uR";
    static struct option long_options[] = {
        {"utc", no_argument, 0, 'u'},
        {"universal", no_argument, 0, 'u'},
        {"rfc-2822", no_argument, 0, 'R'},
        {0, 0, 0, 0}
    };

    int opt, option_index = 0;
    while ((opt = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1) {
        switch (opt) {
            case 'u':
                flag_u = 1;
                break;
            case 'R':
                flag_r = 1;
                break;
            case '?':
                if (optopt == 0)
                    long_error(argv, optind);
                else
                    short_error(argv, optopt);
                return EXIT_FAILURE;
            default:
                error_print(argv);
                return EXIT_FAILURE;
        }
    }

    time(&t);
    timeinfo = flag_u ? gmtime(&t) : localtime(&t);

    if (flag_r) {
        strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S %z", timeinfo);
    } else {
        strftime(buffer, sizeof(buffer), "%a %b %e %H:%M:%S %Z %Y", timeinfo);
    }

    printf("%s\n", buffer);
    return 0;
}
