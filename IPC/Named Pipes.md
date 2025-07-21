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
## 
