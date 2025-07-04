#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

#define SIZE 1024
int main()
{
	int fd;
	ssize_t bytes;
	char buffer[SIZE];

	fd=open("data.csv",O_RDONLY);
	if(fd<0)
	{
		perror("open");
		return 1;
	}
	while((bytes=read(fd,buffer,sizeof(buffer))) > 0)
	{
		if(write(STDOUT_FILENO,buffer,bytes) != bytes)
		{
			perror("write");
			close(fd);
			return 1;
		}
	}
	if(bytes < 0)
	{
		perror("read");
		close(fd);
		return 1;
	}

	close(fd);
	return 0;
}
