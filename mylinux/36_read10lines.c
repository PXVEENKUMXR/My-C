#include<fcntl.h>
#include<unistd.h>
#include<string.h>

#define SIZE 1024

int main()
{
	int fd=open("log.txt",O_RDONLY);
	if(fd < 0)
	{
		const char *err ="Failed to open file\n";
		write(1,err,strlen(err));
		return 1;
	}
	char buf[SIZE];
	char line[SIZE];
	int bytes;
	int lines = 0;
	int lines_print = 0;

	while((bytes = read(fd,buf,SIZE)) >0 && lines_print < 10 )
	{
		for(int i=0; i< bytes && lines_print < 10;i++)
		{
			line[lines++] = buf[i];
			if(buf[i] == '\n')
			{
				write(1,line,lines);
				lines = 0;
				lines_print++;
			}
		}
	}

	if(lines > 0 && lines_print < 10)
	{
		write(1,line,lines);
	}

	close(fd);
	return 0;
}

