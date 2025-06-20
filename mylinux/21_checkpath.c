#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
    struct stat path_stat;
    const char *path="/home/praveenkumar/mylinux/";
    if (stat(path, &path_stat) != 0) {
        perror("stat");
        return 1;
    }

    if (S_ISREG(path_stat.st_mode)) 
    {
        printf("'%s' is a regular file.\n", path);
    }
    else if (S_ISDIR(path_stat.st_mode))
    {
	    printf("'%s' is a directory.\n", path);
    }
    else
    {
        printf("'%s' is neither a regular file nor a directory.\n", path);
    }

    return 0;
}

