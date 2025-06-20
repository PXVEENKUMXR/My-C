#include<stdio.h>
#include<unistd.h>


int main()
{
	const char *filename = "data.txt";
	if(access(filename,R_OK) == 0)
	{
		printf("File '%s' is readable\n",filename);
	}
	else
	{
		perror("File is not readable");
	}
	return 0;
}
