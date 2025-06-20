#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>
#include<string.h>
#include<sys/stat.h>
#include<unistd.h>

#define PATH_LEN 4096
int main()
{
	DIR *dir;
	struct dirent *start;
	struct stat st;
	char path[PATH_LEN];
	int file=0;
	dir=opendir("Images");
	if(!dir)
	{
		perror("opendir");
		return 1;
	}
	while((start=readdir(dir)) !=NULL)
	{
		if(strcmp(start->d_name,".") == 0 || strcmp(start->d_name,"..") == 0)
		{
			continue;
		}

		snprintf(path,sizeof(path),"Images/%s",start->d_name);

		if(stat(path,&st) == -1)
		{
			perror("stat");
			continue;
		}

		if(S_ISREG(st.st_mode))
		{
			file++;
		}
	}

	closedir(dir);

	char buffer[128];
	int len=snprintf(buffer,sizeof(buffer),"Number of files: %d\n",file);
	write(STDOUT_FILENO,buffer,len);
	return 0;
}
