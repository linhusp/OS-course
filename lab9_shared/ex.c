#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 256

int main(int argc, char* argv[])
{
    int *share_mem, share_mem_id, k;
    key_t key;
    if ((key = ftok(".", 'a')) == -1)
    {
        perror("key\n");
        return 1;
    }

    if ((share_mem_id = shmget(key, SIZE, IPC_CREAT | 0666)) == -1)
    {
        perror("share memory created\n");
        return 2;
    }

    share_mem = (int*) shmat(share_mem_id, 0, 0);

    switch(fork())
    {
        case -1: 
            perror("fork error\n");
            return 4;
        case 0:
            share_mem[0] = atoi(argv[1]);
            share_mem[1] = atoi(argv[2]);
            sleep(3);
            printf("%d + %d = %d\n", share_mem[0], share_mem[1], share_mem[2]);
            shmdt((void*) share_mem);
            shmctl(share_mem_id, IPC_RMID, (struct shmid_ds*)0);
            return 0;
        default:
            sleep(1);
            share_mem[2] = share_mem[1] + share_mem[0];
            shmdt((void*) share_mem);
            sleep(5);
            return 0;
    }

    return 0;
}
