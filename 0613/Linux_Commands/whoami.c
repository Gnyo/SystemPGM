#include <pwd.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    struct passwd *pw;
    uid_t uid;

    uid = getuid();
    pw = getpwuid(uid);
    if (pw)
    {
        printf("%s\n", pw->pw_name);
    }
    else
    {
        perror("getpwuid() error");
    }

    return 0;
}
