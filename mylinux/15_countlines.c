#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
	int fd=open("01_newfile.c", O_RDONLY);
	if(fd < 0)
	{
		perror("open");
		return 1;
	}

	char data[1024];
	int bytes;
	int count = 0;

	while((bytes=read(fd,data,sizeof(data))) > 0)
	{
		for(int i=0;i<bytes;i++)
		{
			if(data[i] == '\n')
			{
				count++;
			}
		}
	}
	if(bytes < 0)
	{
		perror("read");
		return 1;
	}
	close(fd);
	printf("Total lines in : %d\n",count);
	return 0;
}
