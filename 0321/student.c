#include <stdio.h>

int main() {
    char name[50];
    char studentId[20];

    printf("학번을 입력하세요: ");
    scanf("%s", studentId);

    printf("이름을 입력하세요: ");
    scanf("%s", name);

    printf("\n입력한 정보\n");
    printf("학번: %s\n", studentId);
    printf("이름: %s\n", name);

    return 0;
}
