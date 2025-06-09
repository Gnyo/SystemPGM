#include <stdio.h>
#include <unistd.h>

int main()
{
    char hostname[1024];
    if (gethostname(hostname, sizeof(hostname)) == 0)
    {
        printf("%s\n", hostname);
    }
    else
    {
        perror("gethostname() error");
    }
    return 0;
}
