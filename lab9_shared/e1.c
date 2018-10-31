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
    int *SM, *SM_1, SM_id, SM_1_id;
    key_t key;

    if ((key = ftok(".", 'a')) == -1)
    {
        perror("key\n");
        return 1;
    }

    if ((SM_id = shmget(key, SIZE, IPC_CREAT | 0666)) == -1)
    {
        perror("shared\n");
        return 2;
    }

    if ((SM_1_id = shmget(key, SIZE, IPC_CREAT | 0666)) == -1)
    {
        perror("shared1\n");
        return 2;
    }
    

    SM = (int*) shmat(SM_id, 0, 0);
    SM_1 = (int*) shmat(SM_1_id, 0, 0);
    
    switch(fork())
    {
        case -1:
            perror("fork error\n");
            return 4;
        case 0:
            SM[0] = argc - 1;
            int i, j;
            for (i = 1; i < argc; i++)
            {
                SM[i] = atoi(argv[i]);
            }
            sleep(3);
            printf("sum = %d\n", SM_1[argc + 1]);
            shmdt((void*) SM);
            shmdt((void*) SM_1);
            shmctl(SM_id, IPC_RMID, (struct shmid_ds*) 0);
            return 0;
        default:
            sleep(1);
            for (int a = 0; a < argc; a++)
            {
                SM_1[a] = SM[a];
            }

            int sum = 0;
            for (int b = 1; b < argc; b++)
            {
                sum += SM_1[b];
            }
            SM_1[argc + 1] = sum;
            shmdt((void*) SM);
            shmdt((void*) SM_1);
            sleep(5);
            return 0;
    }

    return 0;
}
