#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main() {
    char path[256];
    struct stat st;

    printf("Enter path: ");
    fgets(path, sizeof(path), stdin);
    path[strcspn(path, "\n")] = '\0';

    if (stat(path, &st) == -1) 
    {
        perror("stat");
        return 1;
    }

    if (S_ISREG(st.st_mode))
    {
        printf("Type: Regular File\n");
    }
    else if (S_ISDIR(st.st_mode))
    {
        printf("Type: Directory\n");
    }
    else if (S_ISLNK(st.st_mode))
    {
	printf("Type: Symbolic Link\n");
    }
    else if (S_ISCHR(st.st_mode))
    {	
	printf("Type: Character Device\n");
    }
    else if (S_ISBLK(st.st_mode))
    {
        printf("Type: Block Device\n");
    }
    else if (S_ISFIFO(st.st_mode))
    {
        printf("Type: FIFO (Named Pipe)\n");
    }
    else if (S_ISSOCK(st.st_mode))
    {
        printf("Type: Socket\n");
    }
    else
    {
        printf("Type: Unknown\n");
    }

    return 0;
}

