#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>
#include<sys/stat.h>
#include<unistd.h>
#include<errno.h>

void remove_dir(const char *path)
{
	struct dirent *entry;
	DIR *dir = opendir(path);
	if(!dir)
	{
		perror("opendir");
		return;
	}

	while((entry = readdir(dir)) != NULL)
	{
		char fullpath[4096];

		if(strcmp(entry->d_name,".") == 0 || strcmp(entry->d_name,"..") == 0)
		{
			continue;
		}

		snprintf(fullpath,sizeof(fullpath),"%s/%s",path,entry->d_name);

		struct stat st;
		if(stat(fullpath,&st) == -1)
		{
			perror("stat");
			continue;
		}
		if(S_ISDIR(st.st_mode))
		{
			remove_dir(fullpath);
		}
		else
		{
			if(unlink(fullpath) == -1)
			{
				perror("unlink");
			}
		}
	}
	if(rmdir(path) == -1)
	{
		perror("rmdir");
	}
}
int main()
{
	remove_dir("Temp");
	return 0;
}
