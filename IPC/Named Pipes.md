# Named Pipes
---
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
