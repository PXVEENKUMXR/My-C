#include<stdio.h>
#include<sys/stat.h>

int main()
{
	const char *file = "sample.txt";


	if(chmod(file,0755) != 0 )
	{
		perror("chmod");
		return 1;
	}
	printf("Permissions for '%s' changed to read-only\n",file);
	return 0;
}
