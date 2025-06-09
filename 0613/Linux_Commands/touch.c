#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <utime.h>
#include <errno.h>

// 오류 메시지 출력 함수
void error_print(char *argv[])
{
    fprintf(stderr, "\033[0;31m"); // red
    fprintf(stderr, "%s: 잘못된 사용방법입니다.\n", argv[0]);
    fprintf(stderr, "\033[0m"); // default
    fprintf(stderr, "사용 방법: %s [-c|--no-create] <파일 이름>\n", argv[0]);
}

// main
int main(int argc, char *argv[])
{
    int no_create = 0;
    char *filename = NULL;

    // 인자 파싱
    if (argc < 2)
    {
        error_print(argv);
        return 1;
    }

    // 옵션 처리
    if (strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "--no-create") == 0)
    {
        no_create = 1;
        if (argc < 3)
        {
            error_print(argv);
            return 1;
        }
        filename = argv[2];
    }
    else
    {
        filename = argv[1];
    }

    // 파일 존재 여부 확인
    struct stat file_stat;
    if (stat(filename, &file_stat) == -1)
    {
        if (no_create)
        {
            // -c 옵션이 있는 경우 파일 생성 안 함
            return 0;
        }

        // 파일이 존재하지 않으면 생성
        FILE *file = fopen(filename, "w");
        if (file == NULL)
        {
            perror("fopen() error");
            return 1;
        }
        fclose(file);
    }
    else
    {
        // 파일이 존재하면 수정 시간 갱신
        if (utime(filename, NULL) == -1)
        {
            perror("utime() error");
            return 1;
        }
    }

    return 0;
}
