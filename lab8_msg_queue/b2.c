#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 128

struct message {
    int type;
    char **content;
};

int main(int argc, char* argv[])
{
    int msg_id;
    int msg_flg = IPC_CREAT | 0666;
    key_t key;
    struct message msg_buf;
    char *temp[3];
    for (int i = 0; i < 3; i++)
    {
        temp[i] = (char*) malloc(SIZE);
    }

    if ((key = ftok(".", 'a')) == -1)
    {
        return 1;
    }

    if ((msg_id = msgget(key, msg_flg)) == -1)
    {
        return 2;
    }

    switch (fork())
    {
        case -1:
            return 3;
        case 0:
            printf("child read data\n");
            FILE *fin = fopen(argv[1], "r");
            for (int i = 0; i < 3; i++)
            {
                fgets(temp[i], sizeof(temp[i]), fin);
                temp[i][strlen(temp[i]) - 1] = '\0';
            }
            fclose(fin);

            msg_buf.type = 1;
            msg_buf.content = temp;

            for (int i = 0; i < 3; i++)
            {
                printf("%s\n", msg_buf.content[i]);
            }

            if (msgsnd(msg_id, &msg_buf, sizeof(struct message), 0) == -1)
            {
                return 4;
            }

            sleep(5);
            return 0;
        default:
            sleep(2);

            if (msgrcv(msg_id, &msg_buf, BUFSIZ, 1, 0) == -1)
            {
                return 5;
            }

            printf("parent received from child:\n");
            
            for (int i = 0; i < 3; i++)
            {
                printf("%s\n", msg_buf.content[i]);
            }
            sleep(4);
            return 0;
    }
    return 0;
}
