#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Flags
#define FLAG_n 1 // 줄바꿈 없음
#define FLAG_e 2 // escape 허용
#define FLAG_E 4 // escape 무시

// \0NNN, \xHH 처리 함수
int parse_octal(const char *str, int *consumed) {
    int val = 0, i = 0;
    while (i < 3 && str[i] >= '0' && str[i] <= '7') {
        val = val * 8 + (str[i] - '0');
        i++;
    }
    *consumed = i;
    return val;
}

int parse_hex(const char *str, int *consumed) {
    int val = 0, i = 0;
    while (i < 2 && isxdigit(str[i])) {
        val *= 16;
        if (isdigit(str[i])) val += str[i] - '0';
        else val += tolower(str[i]) - 'a' + 10;
        i++;
    }
    *consumed = i;
    return val;
}

// escape 해석 출력
void print_with_escapes(const char *str) {
    while (*str) {
        if (*str == '\\') {
            str++;
            switch (*str) {
                case 'a': putchar('\a'); break;
                case 'b': putchar('\b'); break;
                case 'f': putchar('\f'); break;
                case 'n': putchar('\n'); break;
                case 'r': putchar('\r'); break;
                case 't': putchar('\t'); break;
                case 'v': putchar('\v'); break;
                case '\\': putchar('\\'); break;
                case 'x': {
                    int consumed = 0;
                    int val = parse_hex(str + 1, &consumed);
                    if (consumed > 0) {
                        putchar(val);
                        str += consumed;
                    } else {
                        putchar('\\');
                        putchar('x');
                    }
                    break;
                }
                case '0': {
                    int consumed = 0;
                    int val = parse_octal(str + 1, &consumed);
                    if (consumed > 0) {
                        putchar(val);
                        str += consumed;
                    } else {
                        putchar('\\');
                        putchar('0');
                    }
                    break;
                }
                default:
                    putchar('\\');
                    putchar(*str);
                    break;
            }
        } else {
            putchar(*str);
        }
        str++;
    }
}

// 오류 출력
void error_print(char *argv[]) {
    fprintf(stderr, "\033[0;31m%s: 잘못된 사용방법입니다.\033[0m\n", argv[0]);
    fprintf(stderr, "사용 방법: %s \033[0;34m[옵션] <문자열...>\033[0m\n", argv[0]);
}

// main
int main(int argc, char *argv[]) {
    int flags = 0;
    const char *short_options = "neE";
    static struct option long_options[] = {{0, 0, 0, 0}};
    int opt, option_index = 0;

    while ((opt = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1) {
        switch (opt) {
            case 'n': flags |= FLAG_n; break;
            case 'e': flags |= FLAG_e; break;
            case 'E': flags |= FLAG_E; break;
            case '?':
                error_print(argv);
                return 1;
        }
    }

    if (optind >= argc) {
        // 아무 인자도 없을 경우 빈 줄 출력
        if (!(flags & FLAG_n)) printf("\n");
        return 0;
    }

    // 문자열 인자 처리
    for (int i = optind; i < argc; i++) {
        if (i > optind) putchar(' ');
        if (flags & FLAG_e) {
            print_with_escapes(argv[i]);
        } else {
            fputs(argv[i], stdout);
        }
    }

    if (!(flags & FLAG_n)) putchar('\n');
    return 0;
}
