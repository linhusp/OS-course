#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int ec;
    printf("call system exec ls -a\n");
    ec = system("ls -a");

    if (ec != -1)
        printf("call ls -a ok\n");
    
    ec = system("ps -a");

    if (ec != -1)
        printf("call ps -a ok\n");
    
    return 0;
}
