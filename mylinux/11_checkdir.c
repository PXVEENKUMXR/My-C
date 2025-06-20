#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>

int main()
{
	const char *dirname = "Test";
	struct stat st;

	if(stat(dirname,&st) == 0)
	{
		if(S_ISDIR(st.st_mode))
		{
			printf("Directory '%s' exists\n",dirname);
		}
		else
		{
			printf("'%s' exists but is not a directory\n",dirname);
		}
	}
	else
	{
		perror("stat");
		printf("Directory does not exists\n");
	}
	return 0;
}
