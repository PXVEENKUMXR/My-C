#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<dirent.h>
#include<string.h>
#include<unistd.h>

#define MAX_PATH 4096

int moving(const char *str,const char *suffix)
{
	if(!str || !suffix)
	{
		return 0;
	}

	int lenstr=strlen(str);
	int lensuf=strlen(suffix);
	if(lensuf > lenstr)
	{
		return 0;
	}

	return strcmp(str + lenstr - lensuf,suffix) == 0;
}
int main()
{
	const char *log_dir = "Logs";
	if(mkdir(log_dir,0755) == -1)
	{
		perror("mkdir");
	}

	DIR *dir =opendir(".");
	if(!dir)
	{
		perror("opendir");
		return 1;
	}
	struct dirent *entry;

	char oldpath[MAX_PATH];
	char newpath[MAX_PATH];

	while((entry=readdir(dir)) != NULL)
	{
		if(strcmp(entry->d_name,".") == 0 || strcmp(entry->d_name,"..") == 0)
		{
			continue;
		}

		if(moving(entry->d_name,".log"))
		{
			snprintf(oldpath,sizeof(oldpath),"./%s",entry->d_name);
			snprintf(newpath,sizeof(newpath),"./%s/%s",log_dir,entry->d_name);
		
			if(rename(oldpath,newpath) == -1)
			{
				perror("rename");
			}
			else
			{
				printf("Moved %s to %s/\n",entry->d_name,log_dir);
			}
		}
	}
	closedir(dir);
	return 0;
}
