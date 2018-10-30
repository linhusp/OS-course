#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>

struct message
{
    int type;
    char* content;
};

int fact(int n)
{
    if (n == 0 || n == 1)
        return 1;
    return fact(n - 1) * n;
}

int main(int argc, char* argv[])
{
    int message_id, id;
    key_t key;
    struct message my_message;
    int n;
    my_message.content = (char*) malloc(BUFSIZ);

    if ((key = ftok(".", 'a')) == -1)
    {
        perror("key created\n");
        return 1;
    }

    if ((message_id = msgget(key, IPC_CREAT | 0666)) == -1)
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
            my_message.type = 10;
            my_message.content = argv[1];
            n = strlen(my_message.content);
            printf("%s\n", my_message.content);
            n += sizeof(my_message.type);

            if (msgsnd(message_id, &my_message, n, 0) == -1)
            {
                perror("message send\n");
                return 4;
            }            
            sleep(5);
            printf("children receive from parent:\n");

            if (n = msgrcv(message_id, &my_message, BUFSIZ, 11, 0) == -1)
            {
                perror("message receive\n");
                return 5;
            }

            my_message.content[strlen(my_message.content)] = 0;
            printf("%s\n", my_message.content);
            return 0;
        default:
            sleep(1);
            if (n = msgrcv(message_id, &my_message, BUFSIZ, 10, 0) == -1)
            {
                perror("message receive\n");
                return 5;
            }
            
            printf("parent receive from children: \n");
            my_message.content[strlen(my_message.content)] = 0;
            printf("%s\n", my_message.content);
            printf("message from parent\n");
            my_message.content = argv[2];
            n = strlen(my_message.content);
            my_message.type = 11;
            n += sizeof(my_message.type);

            if (msgsnd(message_id, &my_message, n, 0) == -1)
            {
                perror("message send\n");
                return 4;
            }
            sleep(10);
            return 0;
    }
    
    return 0;
}
