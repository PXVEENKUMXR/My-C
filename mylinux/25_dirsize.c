#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define PATH_LEN 4096

int main(void)
{
    DIR *dir;
    struct dirent *entry;
    struct stat st;
    char path[PATH_LEN];
    long long total_size = 0;
    dir = opendir("direct1");
    if (!dir) 
    {
        perror("opendir");
        return 1;
    }
    while ((entry = readdir(dir)) != NULL) 
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
	{
            continue;
	}

        snprintf(path, sizeof(path), "Documents/%s", entry->d_name);
        if (stat(path, &st) == -1) 
	{
            perror("stat");
            continue;
        }

        if (S_ISREG(st.st_mode)) 
	{
            total_size += st.st_size;
        }
    }

    closedir(dir);
    char buffer[128];
    int len = snprintf(buffer, sizeof(buffer), "Total size: %lld bytes\n", total_size);
    write(STDOUT_FILENO, buffer, len);

    return 0;
}

