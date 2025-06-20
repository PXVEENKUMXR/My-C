#include<stdio.h>
#include<dirent.h>
#include<sys/types.h>

int main()
{
	DIR *dir;
	struct dirent *start;

	dir=opendir(".");
	if(dir == NULL)
	{
		perror("opendir");
		return 1;
	}

	printf("Files in current diectory\n");

	while((start=readdir(dir)) != NULL)
	{
		if(start->d_name[0] == '.')
		{
			continue;
		}

		printf("%s\n",start->d_name);
	}
	closedir(dir);
	return 0;
}
