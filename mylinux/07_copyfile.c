#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
	int s_fd,d_fd;
	char data[1024];
	int bytes;
	s_fd = open("sample.txt", O_RDONLY);
	if(s_fd < 0 )
	{
		perror("Error opening file");
		return 1;
	}
	d_fd = open("copyfile.txt",O_WRONLY | O_TRUNC);
	if(d_fd == -1 )
	{
		perror("Error opening file");
		return 1;
	}

	if((bytes=read(s_fd,data,sizeof(data))) != 0)
	{
		write(d_fd,data,bytes);
	}
	
	if(bytes < 0)
	{
		perror("Error reading data");
		return 1;
	}
	printf("Successfully copied data from sample.txt to copyfile.txt\n");
	close(s_fd);
	close(d_fd);
	return 0;
}
