#include <stdio.h>
#include <sys/stat.h>

int main() 
{
    struct stat st;

    if (stat("data.bin", &st) == -1) 
    {
        perror("stat");
        return 1;
    }

    printf("Size of 'data.bin' is %lld bytes\n", (long long)st.st_size);
    return 0;
}

