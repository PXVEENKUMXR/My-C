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
## Write a C program where two processes communicate using message queues. Implement sending and receiving messages between the processes using msgget, msgsnd, and msgrcv.
```c
#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>
#include<sys/wait.h>
#include<unistd.h>

#define KEY 2004
#define SRVTYPE 10

struct queue
{
        long type;
        char data[100];
};

int  main()
{
        int pid = fork();

        int msgid = msgget(KEY, IPC_CREAT | 0666);
        if(msgid == -1)
        {
                perror("msgget");
                exit(EXIT_FAILURE);
        }
        struct queue msg;

        if(pid == 0)
        {
                msg.type = SRVTYPE;
                strcpy(msg.data,"It's from the child to sweet parent.\n");
                msgsnd(msgid,&msg,strlen(msg.data)+1,0);
                printf("[Child] Sent to the message queue for parent.\n");

        }
        else
        {
                msgrcv(msgid,&msg,sizeof(msg.data),SRVTYPE,0);
                printf("[Parent] Read from the message queue\n");
                printf("[Parent] Message : %s",msg.data);

                wait(NULL);

                msgctl(msgid,IPC_RMID,NULL);
        }

        return 0;
}
```
## Implement a program where two processes communicate synchronously using message queues. Ensure that one process waits for the other to finish before proceeding.
```c
#include<stdio.h>
#include<sys/msg.h>
#include<string.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<unistd.h>

#define KEY 1000
struct queue
{
        long type;
        char data[100];
};

int main()
{
        int msgid;
        if((msgid = msgget(KEY,IPC_CREAT | 0666)) < 0)
        {
                perror("msgget");
                return 1;
        }

        int pid = fork();
        if(pid < 0)
        {
                perror("fork failed");
                msgctl(msgid,IPC_RMID,NULL);
                exit(EXIT_FAILURE);
        }

        struct queue msg;
        if(pid == 0)
        {
                if(msgrcv(msgid,&msg,sizeof(msg.data),1,0) < 0)
                {
                        perror("msgrcv");
                        msgctl(msgid,IPC_RMID,NULL);
                        return 1;
                }

                printf("[Child] Received  : %s\n",msg.data);

                sleep(1);

                msg.type = 2;
                strcpy(msg.data,"Hi! This is to my parent.");
                if(msgsnd(msgid,&msg,sizeof(msg.data),0) < 0)
                {
                        perror("msgsnd");
                        msgctl(msgid,IPC_RMID,NULL);
                        return 1;
                }
                printf("[Child] Message sent to parent\n");
                exit(0);
        }
        else
        {
                msg.type = 1;
                strcpy(msg.data, "Hi! This is to my child.");
                if(msgsnd(msgid,&msg,sizeof(msg.data),0) < 0)
                {
                        perror("msgsnd");
                        msgctl(msgid,IPC_RMID,NULL);
                        return 1;
                }
                printf("[Parent] Message sent to child\n");

                if(msgrcv(msgid,&msg,sizeof(msg.data),2,0) < 0)
                {
                        perror("parent msgrcv");
                        msgctl(msgid,IPC_RMID,NULL);
                        exit(EXIT_FAILURE);
                }

                printf("[Parent] Received : %s\n",msg.data);

                wait(NULL);

                msgctl(msgid,IPC_RMID,NULL);
                printf("[Parent] Message queue removed.\n");
        }
        return 0;
}
```
