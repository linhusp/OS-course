#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void* thread1_do(void* ar);
void* thread2_do(void* ar);
void* thread3_do(void* ar);
int factorial(int n);
int sum_to(int n);

struct store {
    int n;
    int f;
    int sum;
};

struct file {
    struct store *store_num;
    char *file_name;
};

int main(int argc, char* argv[])
{
    pthread_t thread1, thread2, thread3;
    struct store store_num;
    store_num.n = atoi(argv[1]);

    struct file fout;
    fout.store_num = &store_num;
    fout.file_name = argv[2];
    if (pthread_create(&thread1, NULL, thread1_do, (void*)&store_num) == 0)
    {
        if (pthread_create(&thread2, NULL, thread2_do, (void*)&store_num) == 0)
        {
            struct file fout;
            fout.store_num = &store_num;
            fout.file_name = argv[2];
            pthread_create(&thread3, NULL, thread3_do, (void*)&fout);
        }
    }

    sleep(1);
    return 0;
}

void* thread1_do(void* ar)
{
    struct store *temp = (struct store*) ar;
    temp->f = factorial(temp->n);
}

void* thread2_do(void* ar)
{
    struct store *temp = (struct store*) ar;
    temp->sum = sum_to(temp->f);
}

void* thread3_do(void* ar)
{
    struct file *temp_file = (struct file*) ar;
    FILE *fout = fopen(temp_file->file_name, "w");
    fprintf(fout, "N = %d\n", temp_file->store_num->n);
    fprintf(fout, "%d! = %d\n", temp_file->store_num->n, temp_file->store_num->f);
    fprintf(fout, "Sum = %d\n", temp_file->store_num->sum);
    fclose(fout);
}

int factorial(int n)
{
    int count = 1;
    for (int i = 1; i <= n; i++)
    {
        count *= i;
    }
    return count;
}

int sum_to(int n)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        count += i;
    }
    return count;
}
