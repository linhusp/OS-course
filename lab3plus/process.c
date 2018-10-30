#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int pid, pid1, pid2;

    pid = fork();

    //A
    if (pid == 0)//new B
    {
        printf("B: id = %d, parrent: A id = %d\n", getpid(), getppid());

        pid1 = fork();

        if (pid1 == 0)//new D
        {
            printf("\tD: id = %d, parrent: B id = %d\n", getpid(), getppid());
        } 
        else if (pid1 > 0)//B
        {
            pid1 = fork();

            if (pid1 == 0)//new E
            {
                printf("\tE: id = %d, parrent: B id = %d\n", getpid(), getppid());
            }
        }
    }
    else if (pid > 0)//A
    {
        pid = fork();

        if (pid == 0)//new C
        {
            printf("C: id = %d, parrent: A id = %d\n", getpid(), getppid());

            pid = fork();

            if (pid == 0)//new H
            {
                printf("\tH: id = %d, parrent: C id = %d\n", getpid(), getppid());
            }
        }
        else if (pid > 0)
        {
            printf("A: id = %d, parrent id : %d\n", getpid(), getppid());
        }
    }
    else
    {
        printf("fork error\n");
    }
    
    return 0;
}
