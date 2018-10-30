#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int a1 = atoi(argv[1]);
    int a2 = atoi(argv[2]);

    if (a1 == 1) 
        printf("sum = %d\n", sum(a2));
    else 
        printf("factorial = %d\n", factorial(a2));
    
    return 0;
}
