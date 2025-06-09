#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char message[1024] = "";

    // Argument Check
    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            strcat(message, argv[i]);
            if (i < argc - 1)
            {
                strcat(message, " ");
            }
        }
    }
    else
    {
        strcpy(message, "y"); // 인자가 없는 경우 기본값 'y'
    }

    // Print - 무한 루프
    while (1)
    {
        printf("%s\n", message);
    }

    return 0;
}
