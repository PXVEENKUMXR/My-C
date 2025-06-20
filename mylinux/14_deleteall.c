#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<unistd.h>
#include<sys/stat.h>
#include<string.h>

int main()
{
	const char *path = "Temp";
	DIR *dir;
	struct dirent *start;
	char file[1024];

	dir=opendir(path);
	if(dir == NULL)
	{
		perror("opendir");
		return 1;
	}

	while((start = readdir(dir)) != NULL)
	{
		if(strcmp(start->d_name,".") == 0 || strcmp(start->d_name,"..") == 0)
		{
			continue;
		}

		snprintf(file,sizeof(file),"%s/%s",path,start->d_name);
		struct stat st;
		if(stat(file,&st) == 0 && S_ISREG(st.st_mode))
		{
			if(unlink(file) != 0)
			{
				perror("unlink");
				return 1;
			}
			else
			{
				printf("Deleted: %s\n",file);
			}
		}
	}
	closedir(dir);
	return 0;
}
