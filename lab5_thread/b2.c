#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void* read_input(void* ar);
void* sum_primes(void* ar);
void* sort(void* ar);
void* write_output(void* ar);
int is_prime(int n);

struct files {
    int arr[1000];
    int primes[1000];
    int prime_size;
    int size;
    int sum;
    char *in;
    char *out;
};

int main(int argc, char* argv[])
{
    pthread_t thread_id[4];
    struct files f1;
    f1.in = argv[1];
    f1.out = argv[2];

    pthread_create(&thread_id[0], NULL, read_input, (void*)&f1);
    sleep(1);

    pthread_create(&thread_id[1], NULL, sum_primes, (void*)&f1);
    sleep(1);
    
    pthread_create(&thread_id[2], NULL, sort, (void*)&f1);
    sleep(1);

    pthread_create(&thread_id[3], NULL, write_output, (void*)&f1);
    sleep(1);

    return 0;
}

void* read_input(void* ar)
{
    struct files *f = (struct files*) ar;
    FILE *fin = fopen(f->in, "r");
    fscanf(fin, "%d", &f->size);

    for (int i = 0; i < f->size; i++)
    {
        fscanf(fin, "%d", &(f->arr[i]));
    }
    fclose(fin);
}

void* sum_primes(void* ar)
{
    struct files *f = (struct files*) ar;
    f->sum = 0;
    f->prime_size = 0;
    for (int i = 0; i < f->size; i++)
    {
        if (is_prime(f->arr[i]))
        {
            f->sum += f->arr[i];
            f->prime_size++;
        }
    }
}

void* sort(void* ar)
{
    struct files *f = (struct files*) ar;
    
    int prime_i = 0;
    for (int i = 0; i < f->size; i++)
    {
        if (is_prime(f->arr[i]))
        {
            f->primes[prime_i] = f->arr[i];
            prime_i++;
        }
    }
    
    int temp;
    for (int i = 0; i < f->prime_size - 1; i++)
    {
        for (int j = i + 1; j < f->prime_size; j++)
        {
            if (f->primes[i] > f->primes[j])
            {
                temp = f->primes[j];
                f->primes[j] = f->primes[i];
                f->primes[i] = temp;
            }
        }
    }
}

void* write_output(void* ar)
{
    struct files *f = (struct files*) ar;
    FILE *fout = fopen(f->out, "w");
    fprintf(fout, "Size of array: %d\n", f->size);
    fprintf(fout, "Value of elements: ");
    for (int i = 0; i < f->size; i++)
    {
        fprintf(fout, "%d ", f->arr[i]);
    }

    fprintf(fout, "\nPrimes: ");
    for (int i = 0; i < f->size; i++)
    {
        if (is_prime(f->arr[i]))
        {
            fprintf(fout, "%d ", f->arr[i]);
        }
    }

    fprintf(fout, "\nSum of Primes: %d\n", f->sum);
    fprintf(fout, "Primes sorted from smallest to highest: ");
    for (int i = 0; i < f->prime_size; i++)
    {
        fprintf(fout, "%d ", f->primes[i]);
    }
    fprintf(fout, "\n");
    fclose(fout);
}

int is_prime(int n)
{
    if (n < 2)
    {
        return 0;
    }
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            return 0;
        }
    }
    return 1;
}
