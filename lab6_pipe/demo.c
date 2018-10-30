#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[])
{
    char result[100];
    int fp[2];
    
    if (argc < 2)
    {
        printf("not enough\n");
        return -1;
    }
    
    if (pipe(fp) == 0)
    {
        switch(fork())
        {
            case -1:
                printf("error\n");
                return -3;
            case 0:
                printf("data from child: %s\n", argv[1]);
                close(fp[0]);
                write(fp[1], argv[1], strlen(argv[1]));
                break;
            default:
                close(fp[1]);
                read(fp[0], result, strlen(argv[1]));
                printf("parent received: %s\n", result);
        }
    }
    else
    {
        printf("pipe error\n");
        return -2;
    }
    return 0;
}
