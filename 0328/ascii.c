#include <stdio.h>

int main() {
    char ch;

    while (1) {
        printf("문자 입력 : ");
        scanf(" %c", &ch);

        if (ch == '0') {
            break;
        }

        if (ch >= 'A' && ch <= 'Z') {
            printf("%c의 소문자는 %c입니다.\n", ch, ch + 32);
        }
        else if (ch >= 'a' && ch <= 'z') {
            printf("%c의 대문자는 %c입니다.\n", ch, ch - 32);
        }
        else {
            printf("영문자만 입력해주세요.\n");
        }
    }

    return 0;
}
