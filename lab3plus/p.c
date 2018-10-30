#include <stdio.h>
#include <unistd.h>

int main()
{
    int pid, pid1;
    pid = fork();
    
    if (pid == 0)
    {
        printf("------B-----------\n");
        printf("B: id = %d\n", getpid());
        printf("parent: A id = %d\n", getppid());
        printf("------end B-------\n");
    }
    else if (pid > 0)
    {
        pid1 = fork();
        
        if (pid1 == 0)
        {
            printf("------C------------\n");
            printf("C: id = %d\n", getpid());
            printf("parent: A id = %d\n", getppid());
            printf("------end C--------\n");
        }
        else if (pid1 > 0)
        {
            printf("------parent of A: id = %d\n", getppid());
        }
    }
    else
    {
        printf("fork error\n");
    }

    return 0;
}
