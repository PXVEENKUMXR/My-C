# File Management 

---

## Write a C program to create a new text file and write "Hello, World!" to it?

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

```
## Develop a C program to open an existing text file and display its contents?

```c       
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main()
{
        int fd;
        const char *filename = "sample.txt";
        int bytes;
        char buffer[512];
        fd=open(filename,O_RDONLY);
        if(fd == -1)
        {
                perror("Error opening file");
                return 1;
        }
        if((bytes=read(fd,buffer,sizeof(buffer))) != 0)
        {
                buffer[bytes]='\0';
                printf("%s",buffer);
        }
        if(bytes < 0 )
        {
                perror("Error reading data");
                close(fd);
                return 1;
        }
        close(fd);
        return 0;
}


