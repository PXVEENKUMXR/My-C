#include<stdio.h>
#include<unistd.h>

int main()
{
	const char *file = "sample.txt";

	if(access(file,F_OK) == 0)
	{
		printf("File '%s' exists\n",file);
	}
	else
	{
		perror("File check");
		return 1;
	}
	return 0;
}
