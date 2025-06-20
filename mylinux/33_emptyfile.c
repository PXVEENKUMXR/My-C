#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
	int fd;
	fd=open("empty.txt",O_WRONLY | O_CREAT | O_TRUNC,0644);
	if(fd < 0)
	{
		perror("open");
		return 1;
	}
	printf("File 'empty.txt' created successfully!\n");

	close(fd);
	return 0;
}
