#include <libgen.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 잘못된 사용 시 빨간색으로 에러 메시지 출력
void error_print(char *prog) {
    fprintf(stderr, "\033[0;31m%s: 잘못된 사용방법입니다.\033[0m\n", prog);
    fprintf(stderr, "사용 방법: %s [-s SUFFIX] [-z] [-a] 파일...\n", prog);
}

// 문자열이 특정 접미사(suffix)로 끝나는지 확인
int ends_with(const char *str, const char *suffix) {
    size_t len_str = strlen(str);
    size_t len_suffix = strlen(suffix);
    if (len_suffix > len_str) return 0;
    return strcmp(str + len_str - len_suffix, suffix) == 0;
}

// basename 출력 함수: suffix 제거, 널 문자 옵션 처리 포함
void print_basename(const char *path, const char *suffix, int zero_terminate) {
    char *base = basename((char *)path);
    if (suffix && ends_with(base, suffix)) {
        base[strlen(base) - strlen(suffix)] = '\0';
    }
    printf("%s", base);
    putchar(zero_terminate ? '\0' : '\n');  // -z 또는 --zero
}

int main(int argc, char *argv[]) {
    int multiple = 0;  // -a 또는 --multiple
    int zero = 0;      // -z 또는 --zero
    const char *suffix = NULL;  // -s 또는 --suffix=SUFFIX

    int i = 1;
    // 옵션 처리 루프
    while (i < argc && argv[i][0] == '-') {
        if (strcmp(argv[i], "--") == 0) {
            i++;
            break;
        } else if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--multiple") == 0) {
            multiple = 1;
        } else if (strcmp(argv[i], "-z") == 0 || strcmp(argv[i], "--zero") == 0) {
            zero = 1;
        } else if (strncmp(argv[i], "--suffix=", 9) == 0) {
            suffix = argv[i] + 9;
            multiple = 1;
        } else if ((strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--suffix") == 0) && i + 1 < argc) {
            suffix = argv[++i];
            multiple = 1;
        } else {
            error_print(argv[0]);
            return 1;
        }
        i++;
    }

    // 처리할 파일명이 없을 경우 에러
    if (i >= argc) {
        error_print(argv[0]);
        return 1;
    }

    // 인자들 처리
    for (; i < argc; i++) {
        print_basename(argv[i], suffix, zero);
    }

    return 0;
}
