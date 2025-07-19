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
## Implement a program to handle the SIGSEGV signal (segmentation fault). 
```c
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void handler(int signal)
{
        printf("Caught sigmentation fault [signal %d]\n",signal);
        exit(EXIT_FAILURE);
}
int main()
{
        if(signal(SIGSEGV,handler) == SIG_ERR)
        {
                perror("signal call failed");
                exit(1);
        }

        printf("PID : %d\n",getpid());
        printf("About to get a sigmentation fault...\n");

        int *ptr = NULL;
        *ptr = 10;

        printf("This line will not printed\n");

        return 0;
}
```
## Create a program to handle the SIGILL signal (illegal instruction). 
```c
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void signal_handler(int signal)
{
        printf("Caught SIGILL (signal %d). Exiting..\n",signal);
        exit(0);
}

int main()
{
        if(signal(SIGILL,signal_handler) ==SIG_ERR)
        {
                perror("signal");
                return 1;
        }

        printf("Process PID : %d\n",getpid());
        printf("About to raise SIGILL..\n");

        raise(SIGILL);

        printf("This line will not print\n");
        return 0;
}
```
## Write a program to handle the SIGABRT signal (abort). 
```c
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void handler(int signal)
{
        printf("Caught SIGABRT [Signal %d]\n",signal);
        exit(EXIT_FAILURE);
}

int main()
{
        if(signal(SIGABRT,handler) == SIG_ERR)
        {
                perror("signal");
                return 1;
        }

        printf("Process PID : %d\n",getpid());

        printf("About to raise abort()...\n");

        abort();

        printf("This line will not be printed\n");
        return 0;
}
```
## Implement a C program to handle the SIGQUIT signal.
```c
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void handler(int signal)
{
        printf("Caught SIGQUIT [SIGNAL %d]\n",signal);
        exit(0);
}
int main()
{
        if(signal(SIGQUIT,handler) == SIG_ERR)
        {
                perror("signal");
                return 1;
        }

        printf("Process PID : %d\n",getpid());
        printf("Try pressing Ctrl+\\ to send SIGQUIT...\n");

        //raise(SIGQUIT);

        while(1)
        {
                pause();
        }
        return 0;
}
```
## Write a program to handle the SIGTSTP signal (terminal stop).
```c
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void handler(int signal)
{
        printf("Caught SIGTSTP [Signal %d].\n",signal);
        exit(0);
}
int main()
{
        if(signal(SIGTSTP,handler) == SIG_ERR)
        {
                perror("signal");
                return 1;
        }

        printf("Process PID : %d\n",getpid());
        printf("Press Ctrl+Z to send SIGSTOP (this would normally stop the process)..\n");

        while(1)
        {
                printf("Running...\n");
                sleep(2);
        }
        return 0;
}
```
## Write a program to handle the SIGVTALRM signal (virtual timer expired). 
```c
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/time.h>
#include<time.h>


void signal_handler(int signal)
{
        printf("Received SIGVTALRM (signal %d) : virtual timer expired!\n",signal);}

int main()
{
        if(signal(SIGVTALRM, signal_handler) == SIG_ERR)
        {
                perror("signal");
                return 1;
        }

        struct itimerval timer;

        timer.it_value.tv_sec = 1;
        timer.it_value.tv_usec = 0;
        timer.it_interval.tv_sec = 1;
        timer.it_interval.tv_usec = 0;

        if(setitimer(ITIMER_VIRTUAL, &timer,NULL) != 0)
        {
                perror("setitimer");
                return 1;
        }

        printf("Press Ctrl+C to exit.\n");

        while(1)
        {
                //Busy running loop
        }
        return 0;
}
```
## Write a program to implement a timer using signals.
```c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd = open("/dev/watchdog", O_RDWR);
    if (fd == -1)
    {
        perror("Failed to open /dev/watchdog");
        return 1;
    }

    printf("Watchdog started. Press Ctrl+C to stop.\n");

    while (1)
    {
        write(fd, "\0", 1);
        sleep(1);
    }

    close(fd);
    return 0;
}
```
## Write a program to demonstrate the use of sigaction() for handling signals.
```c
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>


void handler(int sig)
{
        printf("Caught SIGINT (%d). Exiting..\n",sig);
        exit(0);
}
int main()
{
        struct sigaction sa;
        sa.sa_handler = handler;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags =  0;

        if(sigaction(SIGINT,&sa,NULL) == -1)
        {
                perror("sigaction");
                exit(1);
        }
        printf("Running...Press Ctrl+C\n");
        while(1)
        {
                pause();
        }

        return 0;
}
```
## Write a program to demonstrate how to block signals using sigprocmask().
```c
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void handler(int sig)
{
        printf("Caught SIGINT[%d]. but not terminated\n",sig);
}
int main()
{
        sigset_t block,unblock;

        signal(SIGINT,handler);

        sigemptyset(&block);
        sigaddset(&block,SIGINT);
        sigaddset(&block,SIGQUIT);

        if(sigprocmask(SIG_BLOCK,&block,NULL) == -1)
        {
                perror("sigprocmask");
                exit(1);

        }
        printf("SIGINT and SIGQUIT are now blocked. Try pressing Ctrl+C or Ctrl+(\\)..\n");
        sleep(5);

        sigemptyset(&unblock);
        sigaddset(&unblock,SIGINT);

        if(sigprocmask(SIG_UNBLOCK,&unblock,NULL) == -1)
        {
                perror("sigprocmask");
                exit(1);
        }
        printf("SIGINT is now unblocked. Try pressing Ctrl+C\n");
        sleep(5);

        return 0;
}
```
## Write a program to implement a timer using signals
```c
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

void timer_hand(int sig)
{
        printf("Timer expired. Caught the SIGALRM [%d]\n",sig);
        exit(0);
}
int main()
{
        struct sigaction sa;
        sa.sa_handler = timer_hand;
        sa.sa_flags = 0;
        sigemptyset(&sa.sa_mask);

        if(sigaction(SIGALRM,&sa,NULL) == -1)
        {
                perror("sigaction");
                EXIT_FAILURE;
        }

        printf("Setting a 5-Sec timer..\n");
        alarm(5);
        while(1)
        {
                pause();
        }
        printf("This message will not be displayed\n");
        return 0;
}
```
## Write a program to demonstrate signal handling in a multithreaded environment
```c
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<pthread.h>
#include<unistd.h>

int run = 1;
void handler_signal(int sig)
{
        printf("Received signal %d, stopping..\n",sig);
        run = 0;
}

void *thread(void *arg)
{
        while(run)
        {
                printf("Thread is running..\n");
                sleep(1);
        }
        printf("Thread exiting.\n");
        return NULL;
}

int main()
{
        pthread_t t1;

        signal(SIGINT,handler_signal);

        pthread_create(&t1,NULL,thread,NULL);

        pthread_join(t1,NULL);
        printf("Main thread exiting.\n");
        return 0;
}
```
## Write a program to handle a real-time signal using sigqueue().
```c
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void handler(int sig,siginfo_t *info,void *context)
{
        printf("Received signal: %d\n",sig);
        printf("Data received : %d\n",info->si_value.sival_int);
}

int main()
{
        struct sigaction sa;
        pid_t pid = getpid();

        sa.sa_sigaction = handler;
        sa.sa_flags = SA_SIGINFO;
        sigemptyset(&sa.sa_mask);

        sigaction(SIGRTMIN,&sa,NULL);

        union sigval value;
        value.sival_int = 123;
        sigqueue(pid,SIGRTMIN,value);

        pause();

        return 0;
}
```
## Write a program to handle the SIGTSTP signal and suspend the process.
```c
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

void handle(int sig)
{
        printf("\nCaught SIGTSTP [%d]. Suspending process manually..\n",sig);
        signal(SIGTSTP,SIG_DFL);
        raise(SIGTSTP);
}
int main()
{
        struct sigaction sa;

        sa.sa_handler = handle;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;

        if(sigaction(SIGTSTP,&sa,NULL) == -1)
        {
                perror("sigaction");
                exit(1);
        }
        printf("Running... Press Ctrl+Z to send SIGTSTP.\n");

        while(1)
        {
                printf("Working..\n");
                sleep(2);
        }
        return 0;
}
```
## Write a program to demonstrate IPC using signals
```c
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/wait.h>
#include<unistd.h>

void handler(int sig)
{
        if(sig == SIGINT)
        {
                printf("Received SIGINT signal from child. Terminating..\n");
                exit(0);
        }
}
int main()
{
        int pid = fork();

        if(pid == 0)
        {
                printf("[Child] Waiting for signal from parent [%d]\n",getppid());
                if(signal(SIGINT,handler) < 0)
                {
                        perror("signal");
                        exit(1);
                }

                while(1)
                {
                        pause();
                }
        }
        else
        {
                sleep(3);
                printf("[Parent] Sending SIGINT signal to child[%d]\n",pid);
                kill(pid,SIGINT);

                wait(NULL);
        }

        return 0;
}
```#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

void handle(int sig)
{
        printf("\nCaught SIGTSTP [%d]. Suspending process manually..\n",sig);
        signal(SIGTSTP,SIG_DFL);
        raise(SIGTSTP);
}
int main()
{
        struct sigaction sa;

        sa.sa_handler = handle;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;

        if(sigaction(SIGTSTP,&sa,NULL) == -1)
        {
                perror("sigaction");
                exit(1);
        }
        printf("Running... Press Ctrl+Z to send SIGTSTP.\n");

        while(1)
        {
                printf("Working..\n");
                sleep(2);
        }
        return 0;
}
```

## Write a program to handle the SIGTSTP signal and suspend the process.
```c
