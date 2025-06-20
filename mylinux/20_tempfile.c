#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int main()
{

	char template[] = "/tmp/mytempfileXXXXXX";
	int fd=mkstemp(template);
	if(fd == -1 )
	{
		perror("mkstemp");
		return 1;
	}
	printf("Temporary  file created: %s\n",template);
	const char *data = "This is some temporary data\n";
	if(write(fd,data,strlen(data)) == -1)
	{
		perror("write");
		close(fd);
		return 1;
	}
	printf("Data written to the temporary file\n");
	close(fd);
	return 0;
}
