#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<dirent.h>
#include<string.h>

#define PATH_LEN 4096

int main()
{
	const char *dirname = ".";
	DIR *dir = opendir(dirname);
	struct dirent *entry;
	struct stat st;
	char filepath[PATH_LEN];

	if(!dir)
	{
		perror("opendir");
		return 1;
	}

	int max_size = 0;
	char large_file[PATH_LEN]="";
	while((entry=readdir(dir)) != NULL)
	{
		if(strcmp(entry->d_name,".") == 0 || strcmp(entry->d_name,"..") == 0 || strcmp(entry->d_name,"a.out") == 0)
		{
			continue;
		}

		snprintf(filepath,sizeof(filepath),"%s/%s",dirname,entry->d_name);
		
		if(stat(filepath,&st) == -1)
		{
			continue;
		}

		if(S_ISREG(st.st_mode))
		{
			if(st.st_size > max_size)
			{
				max_size = st.st_size;
				strncpy(large_file,entry->d_name,sizeof(large_file)-1);
				large_file[sizeof(large_file) -1] = '\0';
			}
		}
	}

	closedir(dir);
	if(strlen(large_file) > 0)
	{
		printf("Largest file: %s (%ld bytes)\n",large_file,(long)max_size);
	}
	else
	{
		printf("No regular files found in directory\n");
	}
	return 0;
}

