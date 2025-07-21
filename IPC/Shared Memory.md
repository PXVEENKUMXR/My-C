# Shared Memory
---
## Write a C program that initializes a shared memory segment using shmget.
```c
#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>

#define KEY 9990
#define SIZE 1024

int main()
{
        int shmid;

        shmid = shmget(KEY,SIZE,IPC_CREAT | 0666);
        if(shmid == -1)
        {
                perror("shmget failed");
                exit(EXIT_FAILURE);
        }

        printf("Shared memory segment created with ID : %d\n",shmid);

        return 0;
}
```
## Develop a program that attaches to a previously created shared memory segment using shmat and detaches using shmdt.
```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <string.h>

#define KEY 9990
#define SIZE 1024
int main()
{
        int shmid = shmget(KEY,SIZE,0);

        char *memory;

        if((memory = (char*)shmat(shmid,NULL,0)) < 0)
        {
                perror("shmat");
                shmctl(shmid,IPC_RMID,NULL);
                exit(EXIT_FAILURE);
        }

        strcpy(memory,"This is our shared memory segment.");
        printf("Written data to shared memory.\n");

        printf("Shared memory : %s\n",memory);

        shmdt(memory);
        return 0;
}
```
## Create a program that forks multiple processes, and each process communicates using shared memory.
```c
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>

#define SHM_KEY 1001
#define SHM_SIZE 512

int main()
{
        int shmid = shmget(SHM_KEY,SHM_SIZE, IPC_CREAT |0666);
        pid_t ch1,ch2;

        char *data;

        if((ch1 = fork()) == 0)
        {
                if((data = shmat(shmid,NULL,0)) < 0)
                {
                        perror("shmat");
                        shmctl(shmid,IPC_RMID,NULL);
                        exit(1);
                }
                sprintf(data,"Is this the shared memory ID : %d",shmid);

                printf("Process 1 : Written data to shared memory\n");

                sleep(2);

                printf("Process 1 : Responce -> %s\n",data);
                shmdt(data);
                exit(0);
        }

        if((ch2 = fork()) == 0)
        {
                if((data = shmat(shmid,NULL,0)) < 0)
                {
                        perror("shmat");
                        shmctl(shmid,IPC_RMID,NULL);
                        exit(1);
                }

                printf("Process 2 : Received : %s\n",data);
                sprintf(data,"Yes, This is shared memory ID : %d",shmid);
                printf("Process 2 : Responced to process 1 in shared memory\n");
                sleep(1);
                shmdt(data);
                exit(0);
        }

        wait(NULL);
        wait(NULL);
        shmctl(shmid,IPC_RMID,NULL);
        return 0;
}
```
## Write a program that dynamically creates shared memory segments based on user input
```c
#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<sys/ipc.h>

#define KEY 2004

int main()
{
        int size;
        char *mem;
        int shmid;
        printf("Enter the size of shared memory : ");
        scanf("%d",&size);

        shmid = shmget(KEY,size,IPC_CREAT | 0666);

        if(shmid < 0)
        {
                perror("shmget");
                exit(1);
        }

        mem = (char*)shmat(shmid,NULL,0);

        sprintf(mem,"We have accessed shared memory ID : %d",shmid);

        printf("Shared memory : %s\n",mem);

        shmdt(mem);

        return 0;
}
```
