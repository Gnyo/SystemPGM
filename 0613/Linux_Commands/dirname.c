#include <libgen.h>
#include <stdio.h>

// Function declaration
void error_print(char *argv[])
{
    fprintf(stderr, "\033[0;31m"); // red
    fprintf(stderr, "%s: 잘못된 사용방법입니다.\n", argv[0]);
    fprintf(stderr, "\033[0m"); // default
    fprintf(stderr, "사용 방법: %s ", argv[0]);
    fprintf(stderr, "\033[0;34m"); // blue
    fprintf(stderr, "<경로 + 파일 이름>");
    fprintf(stderr, "\n");
    fprintf(stderr, "\033[0m"); // default
}

// main
int main(int argc, char *argv[])
{
    // Argument Check
    if (argc != 2)
    {
        error_print(argv);
        return 1;
    }
    // Print dirname
    printf("%s\n", dirname(argv[1]));
    return 0;
}