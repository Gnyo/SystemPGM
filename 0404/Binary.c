#include <stdio.h>

// 1의 개수 세기 함수
int countOnes(unsigned char n) {
    int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

// 8비트 이진수 출력 함수
void printBinary(unsigned char n) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (n >> i) & 1);
    }
}

int main() {
    int input;

    printf("0~255 사이의 정수를 입력하세요: ");
    scanf("%d", &input);

    if (input < 0 || input > 255) {
        printf("입력값이 범위를 벗어났습니다.\n");
        return 1;
    }

    unsigned char number = (unsigned char)input;

    printf("2진수: ");
    printBinary(number);
    printf("\n");

    int oneCount = countOnes(number);
    printf("1의 개수: %d개\n", oneCount);

    unsigned char upper4Bits = (number >> 4) & 0x0F;  // 상위 4비트 추출
    printf("상위 4비트: ");
    for (int i = 3; i >= 0; i--) {
        printf("%d", (upper4Bits >> i) & 1);
    }
    printf("\n");

    return 0;
}

