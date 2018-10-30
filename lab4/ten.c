#include <stdio.h>
#include <stdlib.h>

int is_prime(int n);

int main(int argc, char *argv[])
{
    FILE *fin, *fout;
    int data, size;

    fin = fopen(argv[1], "r");
    fscanf(fin, "%d", &size);

    int arr[size];
    for (int i = 0; i < size; i++)
    {
        fscanf(fin, "%d", &arr[i]);
    }
    fclose(fin);

    int sum = 0, c = 0;
    for (int i = 0; i < size; i++)
    {
        if (is_prime(arr[i]))
        {
            sum += arr[i];
            c++;
        }
    }

    fout = fopen(argv[2], "w");
    fprintf(fout, "%d\nsum = %d\n", c, sum);

    int prime_arr[c];
    int prime_i = 0;
    for (int i = 0; i < size; i++)
    {
        if (is_prime(arr[i]))
        {
            fprintf(fout, "%d ", arr[i]);
            prime_arr[prime_i] = arr[i];
            prime_i++;
        }
    }
    fprintf(fout, "\n");

    int temp;
    for (int i = 0; i < c - 1; i++)
    {
        for (int j = i + 1; j < c; j++)
        {
            if (prime_arr[i] > prime_arr[j])
            {
                temp = prime_arr[j];
                prime_arr[j] = prime_arr[i];
                prime_arr[i] = temp;
            } 
        }
    }

    for (int i = 0; i < c; i++)
    {
        fprintf(fout, "%d ", prime_arr[i]);
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
