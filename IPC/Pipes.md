# Pipes 
---
## Implement a program that uses pipes for communication between a parent and childprocess. Show how data can be passed between processes using pipes.
```c
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main()
{
        int fd[2];
        char *send = "Message to the parent.You finished dad!";
        char msg[100];

        if(pipe(fd) < 0)
        {
                perror("pipe");
                exit(1);
        }

        int pid = fork();
        if(pid == 0)
        {
                close(fd[0]);
                write(fd[1],send,strlen(send)+1);
                printf("[Child] Sent to dad.\n");
                close(fd[1]);
        }
        else
        {
                close(fd[1]);
                read(fd[0],msg,sizeof(msg));
                printf("[Parent] : %s\n",msg);
                close(fd[0]);
        }
        return 0;
}
```
## Create a program where two processes communicate synchronously using pipes.Ensure that one process waits for the other to finish before proceeding.
```c
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>

int main()
{
        int fd[2];
        char send[]="I'm not in danger, I am the danger.";
        char msg[100];

        if(pipe(fd) < 0)
        {
                perror("pipe");
                return 1;
        }

        int pid = fork();
        if(pid == 0)
        {
                close(fd[0]);
                write(fd[1],send,strlen(send)+1);
                printf("[Child] Sent to dad! [%d]\n",getppid());
                close(fd[1]);
        }
        else
        {
                close(fd[1]);
                read(fd[0],msg,sizeof(msg));
                printf("[Parent] Message from child : %s\n",msg);
                close(fd[0]);

                wait(NULL);
        }
        return 0;
}
```
## Implement a program that uses Named pipes for communication between two processes.
```c
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/wait.h>

#define FIFO_NAME "YOURNAME"

int main()
{
        unlink(FIFO_NAME);

        int fd;
        if(mkfifo(FIFO_NAME,0644) < 0)
        {
                perror("mkfifo failed");
                return 1;
        }

        char *send = "Message : It is not for fifo.";
        char msg[100];
        fd = open(FIFO_NAME,O_RDWR);
        if(fd == -1)
        {
                perror("open");
                return 1;
        }
        int  pid = fork();
        if(pid == 0)
        {
                write(fd,send,strlen(send)+1);
                printf("[Child] Message sent to yourfifo\n");
        }
        else
        {
                read(fd,msg,sizeof(msg));
                printf("[Parent] FIFO :  %s\n",msg);
                wait(NULL);
        }
        return 0;
}
```
## Write a C program to create a message queue using the msgget system call. Ensurethat the program checks for errors during the creation process
```c
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
```c
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
```c
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
