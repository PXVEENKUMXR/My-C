#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() 
{
    char dirname[64];
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    if (!t) 
    {
        perror("localtime");
        return 1;
    }
    if (strftime(dirname, sizeof(dirname), "%Y-%m-%d-%H-%M-%S", t) == 0) 
    {
        fprintf(stderr, "strftime failed\n");
        return 1;
    }
    if (mkdir(dirname, 0755) == -1) 
    {
        perror("mkdir");
        return 1;
    }
    printf("Directory created: %s\n", dirname);
    return 0;
}

