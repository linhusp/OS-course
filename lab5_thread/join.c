#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* thread1(void* ar)
{
    printf("thread %d\n", *((int*)ar));
    sleep(2);
}

int main(int argc, char* argv[])
{
    pthread_t tid[3];
    int status;
    int *pstatus = &status;

    for (int i = 0; i < 3; i++)
    {
        pthread_create(&tid[i], NULL, thread1, (void*)&tid[i]);
    }
    
    for (int i = 0; i < 3; i++)
    {
        if (pthread_join(tid[i], (void**)pstatus) > 0)
        {
            printf("join thread %d failure\n", (int)tid[i]);
            return 0;
        }

        printf("wait of %d ok, return code %d\n", (int)tid[i], status);
        sleep(1);
    }

    sleep(1);
    return 0;
}
