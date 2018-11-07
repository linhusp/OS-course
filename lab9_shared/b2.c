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
    int *SM, SM_id;
    int shm_flg = IPC_CREAT | 0666;
    key_t key;
    if ((key = ftok(".", 'a')) == -1)
    {
        perror("key created\n");
        return 1;
    }

    if ((SM_id = shmget(key, SIZE, shm_flg)) == -1)
    {
        perror("share memory created\n");
        return 2;
    }

    SM = (int*) shmat(SM_id, 0, 0);

    switch (fork())
    {
        case -1:
            perror("fork error\n");
            return 4;
        case 0:
            FILE *fin = fopen(argv[1], "r");
            fgets(SM[0], "%d", fin);
            fgets(SM[1], "%d", fin);

    }

    return 0;
}
