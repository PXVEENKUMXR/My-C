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
```
## Implement a C program to create a new directory named "Test" in the current 
directory? 

```c
#include<stdio.h>
#include<dirent.h>
#include<sys/stat.h>

int main()
{
        const char *dirname = "Test";
        if(mkdir(dirname,0755) !=0)
        {
                perror("Error creating directory");
                return 1;
        }
        printf("Directory created successfully!\n");
        return 0;
}
```
## Write a C program to check if a file named "sample.txt" exists in the current directory?
```c
#include<stdio.h>
#include<unistd.h>

int main()
{
        const char *file = "sample.txt";

        if(access(file,F_OK) == 0)
        {
                printf("File '%s' exists\n",file);
        }
        else
        {
                perror("File check");
                return 1;
        }
        return 0;
}
```
## Develop a C program to rename a file from "oldname.txt" to "newname.txt"?
```c
#include<stdio.h>
#include<unistd.h>

int main()
{
        const char *oldname = "oldname.txt";
        const char *newname = "newname.txt";

        if(rename(oldname,newname) != 0)
        {
                perror("Error renaming file");
                return 1;
        }
        printf("File renamed successfully!\n");
        return 0;
}


