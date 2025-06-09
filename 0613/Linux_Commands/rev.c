#include <stdio.h>
#include <string.h>

// Function declaration
void reverseString(char *str)
{
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++)
    {
        char temp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = temp;
    }
}

// main
int main()
{
    char line[1024];

    while (fgets(line, sizeof(line), stdin))
    {
        line[strcspn(line, "\n")] = '\0'; // 개행 문자 제거 (널 문자로 대체)
        reverseString(line);              // 문자열 뒤집기
        printf("%s\n", line);
    }

    return 0;
}

// echo "hello world" | ./rev