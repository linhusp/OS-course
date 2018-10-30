#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 

int factorial(int n)
{
    if (n == 0 || n == 1)
        return 1;
    return n * factorial(n - 1);
}

int main(int argc, char* argv[])
{
    int fp[2];
    int result;
    int f;

    if (atoi(argv[1]) <= 3)
    {
        return -1;
    }

    if (pipe(fp) == 0)
    {
        switch(fork())
        {
            case -1:
                printf("error fork()\n");
                return -2;
            case 0:
                printf("child data: %d\n", atoi(argv[1]));
                f = factorial(atoi(argv[1]));
                close(fp[0]);
                write(fp[1], (void*)&f, sizeof(int));
                break;
            default:
                close(fp[1]);
                read(fp[0], (void*)&result, sizeof(int));
                printf("parent data: %d\n", result); 
        }
    }
    else
    {
        printf("error pipe\n");
        return -3;
    }
    
    return 0;
}
