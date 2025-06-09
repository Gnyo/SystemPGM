#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

// 오류 메시지 출력 함수
void error_print(char *argv[]) {
    fprintf(stderr, "\033[0;31m"); // 빨간색
    fprintf(stderr, "%s: 잘못된 사용방법입니다.\n", argv[0]);
    fprintf(stderr, "\033[0m"); // 기본 색상
    fprintf(stderr, "사용 방법: %s ", argv[0]);
    fprintf(stderr, "\033[0;34m"); // 파란색
    fprintf(stderr, "<초 단위 시간>");
    fprintf(stderr, "\n\033[0m"); // 기본 색상
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        error_print(argv);
        return 1;
    }

    char *endptr;
    errno = 0;
    long seconds = strtol(argv[1], &endptr, 10);

    // 유효하지 않은 입력 또는 음수/초과 체크
    if (*endptr != '\0' || errno != 0 || seconds < 0 || seconds > UINT_MAX) {
        error_print(argv);
        return 1;
    }

    sleep((unsigned int)seconds);
    return 0;
}
