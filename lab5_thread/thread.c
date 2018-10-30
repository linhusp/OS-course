#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* thread1(void* ar)
{
    printf("thread %d\n", *((int*)ar));
    sleep(2);
}

int main(int argc, char* argv[])
{
    int n = atoi(argv[1]);
    pthread_t tid[n];

    for (int i = 0; i < n; i++)
    {
        pthread_create(&tid[i], NULL, thread1, (void*) &tid[i]);
    }

    sleep(3);
    
    return 0;
}
