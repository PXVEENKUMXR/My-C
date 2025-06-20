#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<unistd.h>

int main(void)
{
	const char *fifo="myfifo";
	if(mkfifo(fifo,0666) == -1)
	{
		perror("mkfifo");
		return 1;
	}
	write(STDOUT_FILENO,"FIFO 'myfifo' created successfully\n",36);
	return 0;
}
