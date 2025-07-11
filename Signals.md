# Signals
---
## Write a C program to catch and handle the SIGINT signal?
```c
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

void handle_sigint(int sig)
{
        printf("\nCaught SIGINT (signal number %d). Exiting..\n",sig);
        exit(0);
}

int main()
{
        if(signal(SIGINT, handle_sigint) == SIG_ERR)
        {
                perror("signal");
                return 1;
        }

        while(1)
        {
                printf("Running..\n");
                sleep(1);
        }

        return 0;
}
```
## Implement a C program to send a custom signal to another process?
### Sender
```c
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/types.h>

int main()
{
        pid_t target;
        printf("Enter the target process ID : ");
        if(scanf("%d",&target) != 1)
        {
                perror("Failed to scan");
                return 1;
        }

        if(kill(target,SIGUSR1) == -1)
        {
                perror("Failed to send SIGUSR1 Signal");
                return 1;
        }
        printf("SIGUSR1 Signal sent successfully to process : %d\n",target);
        return 0;
}
```
### Receiver
```c
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

void handle_signal(int sig)
{
        printf("Receiver caught the signal : %d\n",sig);
        exit(0);
}
int main()
{

        if(signal(SIGUSR1,handle_signal) == SIG_ERR)
        {
                perror("Failed to send signal");
                return 1;
        }

        printf("Receiver running with PID : %d\n",getpid());

        while(1)
        {
                printf("Running..\n");
                sleep(1.5);
        }
        return 0;
}
```
## Create a C program to ignore the SIGCHLD signal temporarily?
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main()
{
    struct sigaction sa_old, sa_ignore;

    sa_ignore.sa_handler = SIG_IGN;
    sigemptyset(&sa_ignore.sa_mask);
    sa_ignore.sa_flags = 0;

    if (sigaction(SIGCHLD, &sa_ignore, &sa_old) == -1)
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    printf("SIGCHLD signal temporarily ignored.\n");

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        printf("Child process running (PID: %d)\n", getpid());
        sleep(2);
        printf("Child process exiting.\n");
        exit(0);
    } else
    {
        printf("Parent process waiting (but not for child).\n");
        sleep(3);
    }

    if (sigaction(SIGCHLD, &sa_old, NULL) == -1)
    {
        perror("sigaction restore");
        exit(EXIT_FAILURE);
    }

    printf("SIGCHLD handler restored. Exiting program.\n");
    return 0;
}
```
## Write a program to block the SIGTERM signal using sigprocmask().
```c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main() {
    sigset_t new_set, old_set;

    sigemptyset(&new_set);
    sigaddset(&new_set, SIGTERM);

    if (sigprocmask(SIG_BLOCK, &new_set, &old_set) < 0) {
        perror("sigprocmask");
        exit(EXIT_FAILURE);
    }

    printf("SIGTERM is now blocked. Try sending SIGTERM (kill -15 %d).\n", getpid());
    printf("Sleeping for 30 seconds...\n");
    sleep(30);

    printf("Unblocking SIGTERM.\n");

    if (sigprocmask(SIG_SETMASK, &old_set, NULL) < 0) {
        perror("sigprocmask");
        exit(EXIT_FAILURE);
    }

    printf("SIGTERM is now unblocked. Sleeping for another 30 seconds...\n");
    sleep(30);

    return 0;
}
```
## Implement a C program to handle the SIGALRM signal using sigaction().
```c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_alarm(int signum)
{
    printf("Caught SIGALRM signal (%d)\n", signum);
}

int main()
{
    struct sigaction sa;

    sa.sa_handler = handle_alarm;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGALRM, &sa, NULL) < 0)
{
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    printf("Setting alarm for 5 seconds...\n");
    alarm(5);

    printf("Waiting for SIGALRM...\n");
    pause();
    printf("Program continues after signal handling.\n");
    return 0;
}
```
## Write a C program to install a custom signal handler for SIGTERM?
```c
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void sig_handler(int signal)
{
        printf("Received SIGTERM (signal %d)\Cn",signal);
        exit(0);
}
int main()
{
        if(signal(SIGTERM,sig_handler) == SIG_ERR)
        {
                perror("signal");
                return 1;
        }

        printf("Process PID : %d\n",getpid());
        printf("Waiting for SIGTERM..\n");

        while(1)
        {
                pause();
        }
        return 0;
}
```
## 
