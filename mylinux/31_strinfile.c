#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include<stdio.h>

#define BUF_SIZE 1024

int main() 
{
    int fd, n, i = 0, line_num = 1, found = 0;
    char buf[BUF_SIZE], line[BUF_SIZE], search[100];

    write(1, "Enter string to search: ", 25);
    read(0, search, sizeof(search));
    search[strcspn(search, "\n")] = '\0';

    fd = open("shravya.txt", O_RDONLY);
    if (fd < 0) 
    {
        write(2, "Cannot open file\n", 17);
        return 1;
    }

    while ((n = read(fd, buf, BUF_SIZE)) > 0) 
    {
        for (int j = 0; j < n; j++) 
	{
            line[i++] = buf[j];
            if (buf[j] == '\n') 
	    {
                line[i] = '\0';
                if (strstr(line, search)) 
		{
                    char msg[128];
                    int len = snprintf(msg, sizeof(msg), "Found on line %d: %s", line_num, line);
                    write(1, msg, len);
                    found = 1;
                }
                i = 0;
                line_num++;
            }
        }
    }

    if (!found)
    {
        write(1, "Not found\n", 10);
    }

    close(fd);
    return 0;
}

