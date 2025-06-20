#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>

#define MAX_PATH 4096
#define BUF_SIZE 8192

int textfile(const char *filename)
{
	int len=strlen(filename);
	return (len > 4) & (strcmp(filename+len -4,".txt") == 0);
}

int main()
{
	DIR *dir=opendir(".");

	if(!dir)
	{
		perror("opendir");
		return 1;
	}

	FILE *out=fopen("combined.txt","w");
	if(!out)
	{
		perror("fopen combined.txt");
		closedir(dir);
		return 1;
	}

	struct dirent *entry;
	char buf[BUF_SIZE];

	while((entry=readdir(dir)) != NULL)
	{
		if(entry->d_name[0] == '.')
		{
			continue;
		}

		if(!textfile(entry->d_name))
		{
			continue;
		}
		FILE *in=fopen(entry->d_name,"r");
		if(!in)
		{
			perror("fopen input file");
			continue;
		}
		fprintf(out,"\n----- Contents of %s -------\n",entry->d_name);

		int n;
		while((n = fread(buf,1,sizeof(buf),in)) > 0)
		{
			if(fwrite(buf,1,n,out) !=n)
			{
				perror("fwrite");
				fclose(in);
				fclose(out);
				closedir(dir);
				return 1;
			}
		}
		fclose(in);
	}
	fclose(out);
	closedir(dir);

	printf("All .txt files combined into combined.txt\n");
	return 0;
}

