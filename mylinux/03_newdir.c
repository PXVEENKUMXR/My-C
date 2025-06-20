#include <stdio.h>
#include<dirent.h>
#include<sys/stat.h>

int main()
{
	const char *dirname = "Test";
	if(mkdir(dirname,0755) !=0)
	{
		perror("Error creating directory");
		return 1;
	}
	printf("Directory created successfully!\n");
	return 0;
}
