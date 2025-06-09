#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Flags
#define FLAG_n 1 // 0001
#define FLAG_b 2 // 0010
#define FLAG_s 4 // 0100
#define FLAG_E 8 // 1000

// Function to print lines ending with $
void dollar_print(char str[]) {
    for (int i = 0; i < strlen(str) - 1 && str[i] != '\0'; i++) {
        putchar(str[i]);
    }
    printf("$\n");
}

// Error print functions
void error_print(char *argv[]) {
    fprintf(stderr, "\033[0;31m%s: 잘못된 사용방법입니다.\033[0m\n", argv[0]);
    fprintf(stderr, "사용 방법: %s \033[0;34m[옵션] [파일 이름]\033[0m\n", argv[0]);
}

void short_error(char *argv[], char optopt) {
    fprintf(stderr, "\033[0;31m%s: '-%c'는(은) 인식할 수 없는 옵션입니다.\033[0m\n", argv[0], optopt);
}

void long_error(char *argv[], int optind) {
    fprintf(stderr, "\033[0;31m%s: '%s'는(은) 인식할 수 없는 옵션입니다.\033[0m\n", argv[0], argv[optind - 1]);
}

int main(int argc, char *argv[]) {
    int flags = 0;
    int n = 0;     // 줄 번호
    int count = 0; // 빈 줄 카운트
    char buffer[1024];
    FILE *file = NULL;

    const char *short_options = "nbsE";
    static struct option long_options[] = {
        {"number", no_argument, 0, 'n'},
        {"number-nonblank", no_argument, 0, 'b'},
        {"squeeze-blank", no_argument, 0, 's'},
        {"show-ends", no_argument, 0, 'E'},
        {0, 0, 0, 0}};

    int opt, option_index = 0;
    while ((opt = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1) {
        switch (opt) {
            case 'n': flags |= FLAG_n; break;
            case 'b': flags |= FLAG_b; break;
            case 's': flags |= FLAG_s; break;
            case 'E': flags |= FLAG_E; break;
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

    // 파일 인자 처리 (optind 이후가 파일 이름)
    if (optind < argc) {
        file = fopen(argv[optind], "r");
        if (!file) {
            perror(argv[optind]);
            return EXIT_FAILURE;
        }
    } else {
        file = stdin;
    }

    // 옵션 조합에 따른 출력
    if ((flags & FLAG_b) && !(flags & FLAG_n)) flags &= ~FLAG_n; // b가 있으면 n 무시

    while (fgets(buffer, sizeof(buffer), file)) {
        int is_blank = (buffer[0] == '\n');

        if (flags & FLAG_s) {
            if (is_blank && count > 0) continue;
            count = is_blank ? count + 1 : 0;
        }

        if (flags & FLAG_b && !is_blank) {
            printf("%6d  ", ++n);
        } else if (flags & FLAG_n && !(flags & FLAG_b)) {
            printf("%6d  ", ++n);
        }

        if (flags & FLAG_E) {
            dollar_print(buffer);
        } else {
            fputs(buffer, stdout);
        }
    }

    if (file != stdin) fclose(file);
    return 0;
}