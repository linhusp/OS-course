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
    char **SM;
    int SM_id;
    int SM_flg = IPC_CREAT | 0666;
    key_t key;
    if ((key = ftok(".", 'a')) == -1)
    {
        return 1;
    }

    if ((SM_id = shmget(key, SIZE, SM_flg)) == -1)
    {
        perror("share memory created\n");
        return 2;
    }

    SM = (char**) shmat(SM_id, 0, 0);


    switch (fork())
    {
        case -1:
            perror("fork error\n");
            return 4;
        case 0:
            printf("child read data\n");
            FILE *fin = fopen(argv[1], "r");
            // fgets(SM[0], strlen(SM[0]), fin);
            fscanf(fin, "%s", SM[0]);
            printf("%s\n", SM[0]);
            fclose(fin);
            return 0;
        default:
            sleep(1);
            return 0;
    }

    return 0;
}
