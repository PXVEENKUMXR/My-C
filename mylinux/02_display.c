#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>

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
