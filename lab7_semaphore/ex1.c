#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/errno.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    int sem1, sem2, sem3;
    key_t ipc_key;
    ipc_key = ftok(".", 'v');
    if ((sem1 = semget(ipc_key, 3, IPC_CREAT | 0666)) == -1) 
    {
        perror("error - semget: IPC_CREAT | 0666\n");
    }
    printf("sem1 identifier: %d\n", sem1);

    if ((sem2 = semget(ipc_key, 3, IPC_CREAT | IPC_EXCL | 0666)) == -1)
    {
        perror("error - semget: IPC_CREAT | 0666\n");
    }
    printf("sem2 identifier: %d\n", sem2);


    if ((sem3 = semget(IPC_PRIVATE, 3, 0600)) == -1)
    {
        perror("error - semget: IPC_CREAT | 0666\n");
    }
    printf("sem2 identifier: %d\n", sem3);
    
    return 0;
}
