#include <stdio.h>

// 1�� ���� ���� �Լ�
int countOnes(unsigned char n) {
    int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

// 8��Ʈ ������ ��� �Լ�
void printBinary(unsigned char n) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (n >> i) & 1);
    }
}

int main() {
    int input;

    printf("0~255 ������ ������ �Է��ϼ���: ");
    scanf("%d", &input);

    if (input < 0 || input > 255) {
        printf("�Է°��� ������ ������ϴ�.\n");
        return 1;
    }

    unsigned char number = (unsigned char)input;

    printf("2����: ");
    printBinary(number);
    printf("\n");

    int oneCount = countOnes(number);
    printf("1�� ����: %d��\n", oneCount);

    unsigned char upper4Bits = (number >> 4) & 0x0F;  // ���� 4��Ʈ ����
    printf("���� 4��Ʈ: ");
    for (int i = 3; i >= 0; i--) {
        printf("%d", (upper4Bits >> i) & 1);
    }
    printf("\n");

    return 0;
}

