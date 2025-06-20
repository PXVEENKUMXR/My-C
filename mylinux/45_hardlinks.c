#include <stdio.h>
#include <sys/stat.h>

int main() 
{
    struct stat st;

    if (stat("pk.txt", &st) == -1) 
    {
        perror("stat");
        return 1;
    }

    printf("Number of hard links to 'pk.txt': %lu\n", (unsigned long)st.st_nlink);
    return 0;
}

