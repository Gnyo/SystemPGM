#include <stdio.h>
#include <string.h>
#include "copy.h"

char line[MAXLINE];       // �Է� ��
char longest[MAXLINE];    // ���� �� ��

/* �Է� �� ��� ���� �� �� ����Ʈ */
int main() {
    int len, max = 0;

    while (fgets(line, MAXLINE, stdin) != NULL) {
        len = strlen(line);
        if (len > max) {
            max = len;
            copy(line, longest);
        }
    }

    if (max > 0)  // �Է� ���� �־��ٸ�
        printf("%s", longest);

    return 0;
}

