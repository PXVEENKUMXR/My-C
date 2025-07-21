# Message Queues
---
##  Write a C program to create a message queue using the msgget system call. Ensurethat the program checks for errors during the creation process
```C
#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<unistd.h>
#include<fcntl.h>

#define KEY 9002
int main()
{
        int msgid = msgget(KEY,IPC_CREAT | 0666);
        if(msgid == -1)
        {
                perror("msgget failed");
                exit(EXIT_FAILURE);
        }

        printf("Message queue created successfully with key = %d, ID = %d\n",KEY,msgid);

        msgctl(KEY,IPC_RMID,NULL);

        return 0;
}
```
## Develop two separate C programs, one for sending messages and the other for receiving messages through a created message queue.
### Sender
```C
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<fcntl.h>
#include<string.h>

#define KEY 9002
#define SRVMSG 9
struct buffer
{
        long type;
        char msgtext[256];
};
int main()
{
        int msgid = msgget(KEY,0);
        if(msgid == -1)
        {
                perror("msgget");
                return 1;
        }
        struct buffer msg;
        msg.type = SRVMSG;

        printf("Enter the message for server\n");
        fgets(msg.msgtext,sizeof(msg.msgtext),stdin);
        msg.msgtext[strcspn(msg.msgtext,"\n")] = '\0';

        if(msgsnd(msgid,&msg,strlen(msg.msgtext)+1,0) == -1)
        {
                perror("msgsnd");
                return 1;
        }
        printf("Message sent to server\n");
        return 0;
}
```
### Receiver
```C
#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>

#define KEY 9002
#define SRVMSG 9
struct data
{
        long type;
        char msgtext[100];
};
int main()
{
        int msgid = msgget(KEY,0);
        if(msgid == -1)
        {
                perror("msgget");
                return 1;
        }

        struct data msg;

        if(msgrcv(msgid,&msg,sizeof(msg.msgtext),SRVMSG,0) == -1)
        {
                perror("msgrcv");
                return 1;
        }

        printf("%s\n",msg.msgtext);
        printf("Message read from the server\n");
        return 0;
}
```
## Create a program to remove an existing message queue using the msgctl system call. Ensure that the program prompts the user for confirmation before deleting the message queue.
```c
#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/msg.h>

#define KEY 9002

int main()
{
        int msgid;
        char confirm;

        msgid = msgget(KEY,0);
        if(msgid == -1)
        {
                perror("msgget");
                return 1;
        }

        printf("Message Queue with ID : %d\n",msgid);
        printf("Are you sure you want to delete this message queue? (y/n) : ");
        scanf("%c",&confirm);

        if(confirm == 'y' || confirm == 'Y')
        {
                if(msgctl(msgid,IPC_RMID,NULL) == -1)
                {
                        perror("msgctl -IPC_RMID");
                        return 1;
                }
                printf("Message queue deleted successfully.\n");
        }
        else
        {
                printf("Operation cancelled. Message queue not deleted.\n");
        }
        return 0;
}
```
## 
