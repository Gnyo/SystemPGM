#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

// Flags
#define FLAG_n 1 // 01
#define FLAG_v 2 // 10

// Function declaration
void print_line(char *buffer, int max, FILE *file)
{
    int i = 0;
    while (fgets(buffer, 1024, file) && i < max)
    {
        printf("%s", buffer);
        i++;
    }
}

void error_print(char *argv[])
{
    fprintf(stderr, "\033[0;31m"); // red
    fprintf(stderr, "%s: 잘못된 사용방법입니다.\n", argv[0]);
    fprintf(stderr, "\033[0m"); // default
    fprintf(stderr, "사용 방법: %s ", argv[0]);
    fprintf(stderr, "\033[0;34m"); // blue
    fprintf(stderr, "[옵션] [파일 이름]");
    fprintf(stderr, "\n");
    fprintf(stderr, "\033[0m"); // default
}

void short_error(char *argv[], char optopt)
{
    fprintf(stderr, "\033[0;31m"); // red
    fprintf(stderr, "%s: '-%c'는(은) 인식할 수 없는 옵션입니다.\n", argv[0], optopt);
    fprintf(stderr, "\033[0m"); // default
}

void long_error(char *argv[], int optind)
{
    fprintf(stderr, "\033[0;31m"); // red
    fprintf(stderr, "%s: '%s'는(은) 인식할 수 없는 옵션입니다.\n", argv[0], argv[optind - 1]);
    fprintf(stderr, "\033[0m"); // default
}

// main
int main(int argc, char *argv[])
{
    int flags = 0;
    int n = 10;        // Line counting
    char buffer[1024]; // Text buffer
    char *filename = NULL;
    FILE *file = NULL;

    // option
    int opt;
    int option_index = 0;
    const char *short_options = "nv";
    static struct option long_options[] = {
        {"lines", no_argument, 0, 'n'}, {"verbose", no_argument, 0, 'v'}, {0, 0, 0, 0}};

    // Parse options
    while ((opt = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1)
    {
        switch (opt)
        {
        case 'n':
            flags |= FLAG_n;
            break;
        case 'v':
            flags |= FLAG_v;
            break;
        case '?':
            if (optopt == 0)
            { // Long option error
                long_error(argv, optind);
            }
            else
            { // Short option error
                short_error(argv, optopt);
            }
            exit(EXIT_FAILURE);
        default:
            error_print(argv);
            exit(EXIT_FAILURE);
        }
    }

    // Arguments Check
    if (argc == 4) // Use option
    {
        if (flags == 0b01 || flags == 0b11) // n, vn
        {
            filename = argv[3];
            n = atoi(argv[2]);
        }
        else // v
        {
            error_print(argv);
            exit(EXIT_FAILURE);
        }
    }
    else if (argc == 3)
    {
        if (flags == 0b10) // v
        {
            filename = argv[2];
        }
        else // vn, n
        {
            error_print(argv);
            exit(EXIT_FAILURE);
        }
    }
    else if (argc == 2) // No option
    {
        filename = argv[1];
    }
    else // No arguments
    {
        file = stdin;
        int c = getc(file);
        while (c != EOF)
        {
            putc(c, stdout);
            c = getc(file);
        }
        return 0;
    }

    // File open
    file = fopen(filename, "r");

    // Not exist file
    if (file == NULL)
    {
        file = fopen(argv[1], "w");
        while (fgets(buffer, sizeof(buffer), stdin) != NULL)
        {
            fputs(buffer, file);
        }

        fclose(file);
        return 0;
    }

    // Exist file
    // Execute options
    if (flags == 0b01) // n
    {
        print_line(buffer, n, file);
    }
    else if (flags == 0b10) // v
    {
        printf("==> %s <==\n", filename);
        print_line(buffer, n, file);
    }
    else if (flags == 0b11) // vn
    {
        printf("==> %s <==\n", filename);
        print_line(buffer, n, file);
    }
    else
    {
        print_line(buffer, n, file);
    }

    // File close
    fclose(file);
    return 0;
}
