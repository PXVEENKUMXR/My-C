# File Management 

---

## 1 .Write a C program to create a new text file and write "Hello, World!" to it?

```c
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#define FILENAME "newfile.txt"
int main()
{
        int fd;
        const char *data = "Hello, World!\n";
        int bytes;
        fd=open(FILENAME,O_WRONLY | O_CREAT | O_TRUNC,0755);
        if(fd == -1)
        {
                perror("Error opening file");
                return 1;
        }

        if((bytes=write(fd,data,strlen(data))) == -1)
        {
                perror("Error writing data");
                close(fd);
                return 1;
        }
        printf("Hello, World! written successfully\n");
        close(fd);
        return 0;
}
