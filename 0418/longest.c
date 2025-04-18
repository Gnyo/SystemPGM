#include <stdio.h>
#include <string.h>

#define MAXLINE 100

char line[MAXLINE];     // �Է� ��
char longest[MAXLINE];  // ���� �� ��

void copy(char from[], char to[]);

/* �Է� �� ��� ���� �� �� ����Ʈ */
int main() {
    int len, max = 0;

    // �� �پ� �Է��� ������ ���� �� ���� ã��
    while (fgets(line, MAXLINE, stdin) != NULL) {
        len = strlen(line);
        if (len > max) {
            max = len;
            copy(line, longest);
        }
    }

    // �Է� ���� �ϳ��� �־����� ���
    if (max > 0)
        printf("%s", longest);

    return 0;
}

/* copy: from�� to�� ����; to�� ����� ũ�ٰ� ���� */
void copy(char from[], char to[]) {
    int i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}

