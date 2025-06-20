#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
	int fd;
	const char *data = "Goodbye!";
	int bytes;
	fd=open("message.txt",O_WRONLY | O_APPEND);
	bytes=write(fd,data,sizeof(data));
	if(bytes < 0)
	{
		perror("write");
		return 1;
	}
	printf("'%s' appended with message.txt\n",data);
	close(fd);
	return 0;
}
