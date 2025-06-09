#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

int main(int argc, char *argv[]) {
    int use_physical = 0;
    int opt;

    while ((opt = getopt(argc, argv, "P")) != -1) {
        switch (opt) {
            case 'P':
                use_physical = 1;
                break;
            case '?':
                fprintf(stderr, "사용 방법: %s [-P]\n", argv[0]);
                return 1;
        }
    }

    char path[1024];

    if (use_physical) {
        if (realpath(".", path) != NULL) {
            printf("%s\n", path);
        } else {
            perror("realpath() error");
        }
    } else {
        if (getcwd(path, sizeof(path)) != NULL) {
            printf("%s\n", path);
        } else {
            perror("getcwd() error");
        }
    }

    return 0;
}
