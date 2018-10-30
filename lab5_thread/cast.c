#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

struct arr 
{
    int n;
    int a[10];
};

void* thread1(void* ar)
{
    struct arr *ap = (struct arr*) ar;

    for (int count = 0; count < ap->n; count++)
    {
        printf("%d\t", ap->a[count]);
    }

    printf("\n");
}

int main(int argc, char* argv[])
{
    struct arr ar;
    ar.n = 5;
    
    for (int i = 0; i < ar.n; i++)
    {
        ar.a[i] = i + 2;
    }

    pthread_t tid;
    pthread_create(&tid, NULL, &thread1, &ar);
    sleep(2);
    return 0;
}
