#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>

#define SIZE 1024
int main()
{
	int fd= open("binary.bin",O_RDONLY);
	if(fd < 0)
	{
		perror("open");
		return 1;
	}

	unsigned char buffer[SIZE];
	int bytes;

	while((bytes = read(fd,buffer,SIZE)) > 0)
	{
		for(int i=0;i<bytes;i++)
		{
			printf("%02x",buffer[i]);
			if((i+1) % 16 == 0)
			{
				printf("\n");
			}
		}
	}
	if(bytes < 0)
	{
		perror("read");
	}
	close(fd);
	return 0;
}
