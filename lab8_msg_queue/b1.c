#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 128

struct message 
{
    int type;
    char *content;
};

int factorial(int n)
{
    if (n == 0 || n == 1)
    {
        return 1;
    }
    return n * factorial(n - 1);
}

void reverse(char* s)
{
    char temp;
    for (int i = 0, j = strlen(s) - 1; i < j; i++, j--)
    {
        temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    }
}

void itoa(int n, char* s)
{
    int i = 0;
    do
    {
        s[i] = n % 10 + '0';
        i++;
    } while ((n = n / 10) > 0);

    s[i] = '\0';
    reverse(s);
}

int main(int argc, char* argv[])
{
    int msg_id;
    int msg_flg = IPC_CREAT | 0666;
    key_t key;
    struct message msg_buf;

    if (atoi(argv[1]) <= 3)
    {
        return -1;
    }

    key = ftok(".", 'a');
    if (key == -1)
    {
        perror("key created\n");
        return 1;
    }

    msg_id = msgget(key, msg_flg);
    if (msg_id == -1)
    {
        perror("queue created\n");
        return 2;
    }

    switch (fork())
    {
        case -1:
            perror("fork error\n");
            return 3;
        case 0:
            msg_buf.type = 1;
            msg_buf.content = argv[1]; 
            printf("child received: %s\n", msg_buf.content);

            if (msgsnd(msg_id, &msg_buf, sizeof(struct message), 0) == -1)
            {
                perror("message send\n");
                return 4;
            }

            sleep(5);

            printf("child received from parent:\n");
            if (msgrcv(msg_id, &msg_buf, SIZE, 2, 0) == -1)
            {
                perror("message receive\n");
                return 5;
            }

            printf("%s\n", msg_buf.content);
            return 0;
        default:
            sleep(1);

            if (msgrcv(msg_id, &msg_buf, SIZE, 1, 0) == -1)
            {
                perror("message receive\n");
                return 5;
            }

            printf("parent received from children:\n");
            printf("%s\n", msg_buf.content);
    
            char temp[SIZE];
            itoa(factorial(atoi(msg_buf.content)), temp);
            msg_buf.content = temp;
            msg_buf.type = 2;
            if (msgsnd(msg_id, &msg_buf, sizeof(struct message), 0) == -1)
            {
                perror("message send\n");
                return 4;
            }
            sleep(4);
            return 0;
    }
    return 0;
}
