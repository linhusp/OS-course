#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int is_prime(int n);
int find_min(int* arr, int n);
int find_max(int* arr, int n);

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int n;
    printf("n = ");
    scanf("%d", &n);
    int arr[n];
    int c = 0;

    for (int i = 0; i < n; i++)
    {
        while(1)
        {
            int r = rand() % 1000 - 1;
            if (is_prime(r))
            {
                arr[c] = r;
                c++;
                break;
            }
        }
    }

    FILE *fout = fopen(argv[1], "w");
    fprintf(fout, "%d\n", n);
    fprintf(fout, "min = %d\n", find_min(arr, n));
    fprintf(fout, "max = %d\n", find_max(arr, n));

    for (int i = 0; i < n; i++)
    {
        fprintf(fout, "%d ", arr[i]);
    }
    fprintf(fout, "\n");
    
    fclose(fout);

    return 0;
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

int find_min(int* arr, int n)
{
    int min = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] < min)
        {
            min = arr[i];
        }
    }
    return min;
}

int find_max(int* arr, int n)
{
    int max = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}
