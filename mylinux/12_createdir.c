#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>

int main()
{
	const char *dir = "../Backup";

	if(mkdir(dir,0755)!=0)
	{
		perror("Error creating directory");
		return 1;
	}
	printf("Directory '%s' created successfully\n",dir);
	return 0;
}
