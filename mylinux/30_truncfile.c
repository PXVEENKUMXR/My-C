#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc,char *argv[])
{
	const char *file="praveen.txt";
	int length;

	if(argc!=2)
	{
		write(STDOUT_FILENO,"Usage: ./truncate_file\n",24);
		return 1;
	}
	length=atoll(argv[1]);
	if(length < 0)
	{
		write(STDOUT_FILENO, "Length must be non-negative\n",28);
		return 1;
	}

	if(truncate(file,length) == -1)
	{
		perror("truncate");
		return 1;
	}
	write(STDOUT_FILENO,"File truncated successfully!\n",28);
	return 0;
}
