#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/stat.h>

int main()
{
	int fd_in,fd_out;
	struct stat st;

	fd_in = open("log.txt",O_RDONLY);
	if(fd_in < 0)
	{
		perror("open log.txt");
		return 1;
	}

	if(fstat(fd_in,&st) == -1)
	{
		perror("fstat");
		close(fd_in);
		return 1;
	}
	int size = st.st_size;
	fd_out = open("logout.txt",O_WRONLY | O_CREAT | O_TRUNC,0644);
	if(fd_out < 0)
	{
		perror("open logout.txt");
		close(fd_in);
		return 1;
	}

	char ch;
	for(int i=size-1;i>= 0;i--)
	{
		if(lseek(fd_in,i,SEEK_SET) == -1)
		{
			perror("lseek");
			break;
		}
		if(read(fd_in,&ch,1) != 1)
		{
			perror("read");
			break;
		}
		if(write(fd_out,&ch,1) != 1)
		{
			perror("write");
			break;
		}
	}

	close(fd_in);
	close(fd_out);

	printf("Reversed content written to logout.txt\n");
	return 0;
}
