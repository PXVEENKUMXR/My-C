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
## Design a multithreaded program where threads communicate through named pipes.
```c
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<pthread.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

#define F_NAME "THREAD_FIFO"

void *write_thread(void *val)
{
        sleep(1);
        int fd = open(F_NAME,O_WRONLY);

        char *msg = "Hey, Its for thread 2!";

        write(fd,msg,strlen(msg)+1);
        printf("Write thread : Sent to thread 2\n");

        close(fd);
        pthread_exit(NULL);
}
void *read_thread(void *arg)
{
        char buf[100];

        int fd = open(F_NAME,O_RDONLY);

        read(fd,buf,sizeof(buf));
        printf("Read thread : %s\n",buf);

        close(fd);
        pthread_exit(NULL);
}
int main()
{
        if(mkfifo(F_NAME,0666) < 0)
        {
                perror("mkfifo failed");
        }
        pthread_t th1,th2;

        pthread_create(&th1,NULL,write_thread,NULL);
        pthread_create(&th2,NULL,read_thread,NULL);

        pthread_join(th1,NULL);
        pthread_join(th2,NULL);

        unlink(F_NAME);
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
