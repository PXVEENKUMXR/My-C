#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<dirent.h>
#include<string.h>
#include<unistd.h>

#define PATH_LEN 4000

int get_size(const char *path)
{
	struct stat st;
	int size = 0;

	if(stat(path,&st) == -1)
	{
		perror("stat");
		return 1;
	}

	if(S_ISREG(st.st_mode))
	{
		return st.st_size;
	}

	if(S_ISDIR(st.st_mode))
	{
		DIR *dir = opendir(path);
		if(!dir)
		{
			perror("opendir");
			return 0;
		}
		struct dirent *entry;
		char fullpath[PATH_LEN];

		while((entry = readdir(dir)) != NULL)
		{
			if(strcmp(entry->d_name,".") == 0 || strcmp(entry->d_name,"..") ==0)
			{
				continue;
			}

			snprintf(fullpath,sizeof(fullpath),"%s/%s",path,entry->d_name);
			size += get_size(fullpath);
		}
		closedir(dir);
	}
	return size;
}

int main(int argc,char *argv[])
{
	const char *dir = ".";
	if(argc > 1)
	{
		dir=argv[1];
	}
	int total = get_size(dir);
	printf("Total size of all file in '%s' (including subdirectories): %lld bytes\n",dir,(long long)total);
	return 0;
}
