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
