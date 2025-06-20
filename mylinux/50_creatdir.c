#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() 
{
    const char *dirname = "Documents";
    if (mkdir(dirname, 0755) == -1) 
    {
        perror("mkdir");
        return 1;
    }

    printf("Directory '%s' created successfully.\n", dirname);
    return 0;
}

