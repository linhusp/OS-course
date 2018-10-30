#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    int i1 = atoi(argv[1]);
    int i2 = atoi(argv[2]);
    char* op = argv[3];
    int fp[2];
    float result;

    if (i2 == 0)
    {
        printf("second integer can't equal zero\n");
        return -1;
    }

    if (pipe(fp) == 0)
    {
        switch(fork())
        {
            case -1:
                printf("error fork()\n");
                return -2;
            case 0:
                if (*op == '+')
                {
                    result = i1 + i2; 
                }
                else if (*op == '-')
                {
                    result = i1 - i2;
                }
                else if (*op == '*')
                {
                    result = i1 * i2;
                }
                else 
                {
                    result = (float)i1 / i2;
                }
                close(fp[0]);
                write(fp[1], (void*)&result, sizeof(float));
                break;
            default:
                close(fp[1]);
                read(fp[0], (void*)&result, sizeof(float));
                FILE *fout = fopen("result", "w");
                fprintf(fout, "result: %.2f\n", result);
                fclose(fout);
        }
    }
    else
    {
        printf("error pipe\n");
        return -3;
    }

    return 0; 
}
