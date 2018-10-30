#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <sys/errno.h>
#include <time.h>

#define NS 3

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short int *array;
    struct seminfo *_buf;
};

int main(int argc, char* argv[])
{
    int sem_id, sem_value, i;
    struct semid_ds sem_buf;
    unsigned short int sem_array[NS] = {7, 3, 9};
    union semun arg;
    key_t ipc_key;

    if ((sem_id = semget(ipc_key, NS, IPC_CREAT | 0666)) == -1) 
    {
        perror("error - semget: IPC_CREAT | 0666\n");
        return 1;
    }
    printf("semaphore identifier: %d\n", sem_id);

    arg.buf = &sem_buf;
    if (semctl(sem_id, 0, IPC_STAT, arg) == -1)
    {
        perror("semctl: IPC_STAT");
        return 2;
    } 

    arg.array = sem_array;
    if (semctl(sem_id, 0, SETALL, arg) == -1)
    {
        perror("semctl: SETALL\n");
        return 3;
    }

    for (i = 0; i < NS; i++)
    {
        if ((sem_value = semctl(sem_id, i, GETVAL, 0)) == -1)
        {
            perror("semctl: GETVAL\n");
            return 4;
        }
        printf("semaphore %d has value %d\n", i, sem_value);
    }

    printf("\n");

    int x;
    printf("input new val for semaphore 1: ");
    scanf("%d", &x);
    semctl(sem_id, 1, SETVAL, x);
    sem_value = semctl(sem_id, 1, GETVAL, 0);

    printf("new val of semaphore 1: %d\n", sem_value);
    if (semctl(sem_id, 0, IPC_RMID, 0) == -1)
    {
        perror("semctl: IPC_RMID\n");
        return 5;
    }
    return 0;
}
