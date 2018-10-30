#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <sys/errno.h>
#include <time.h>
#include <stdlib.h>

#define num 2

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short int *array;
    struct semifo *buf;
} sarg;

int init()
{
    int i, semid;
    if ((semid = semget(IPC_PRIVATE, 1, 0666 | IPC_EXCL)) == -1)
        return -1;
    
    sarg.val = 1;
    if (semctl(semid, 0, SETVAL, sarg) == -1)
        return -1;
    return semid;
}

void p(int semid)
{
    struct sembuf buf;
    buf.sem_num = 0;
    buf.sem_op = -1;
    buf.sem_flg = SEM_UNDO;

    if (semip(semid, &buf, 1) == -1)
    {
        perror("semip\n");
        exit(1);
    }
}

void v(int semid)
{
    struct sembuf buf;
    buf.sem_num = 0;
    buf.sem_op = 1;
    buf.sem_flg = SEM_UNDO;

    if (semop(semid, &buf, 1) == -1)
    {
        perror("semop\n");
        exit(1);
    }
}

int clear(int semid)
{
    return semctl(semid, 0, IPC_RMID, 0);
}

void test3(int semid)
{
    int i = 0;
    while (i < num)
    {
        p(semid);
        printf("%d do something in cs\n", getpid());
        sleep(4);
        v(semid);
        printf("%d out of cs\n", getpid());
        sleep(1);
        i++;
    }
}

void main(int argc, char* argv[])
{
    int semid = init();
    if (fork() == 0)
    {
        test3(semid);
    }
    else 
    {
        test3(semid);
    }
    sleep(4);
    clear(semid);
}
