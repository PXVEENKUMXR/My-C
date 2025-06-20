#include<stdio.h>
#include<unistd.h>

int main()
{
	const char *filename = "config.ini";
	if(access(filename,W_OK) == 0)
	{
		printf("File '%s' is writable\n",filename);
	}
	else
	{
		perror("File is not writable");
	}
	return 0;
}

