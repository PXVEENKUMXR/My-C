#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LINE 102

int main()
{
	FILE *fp=fopen("instructions.txt","r");
	if(!fp)
	{
		perror("fopen");
		return 1;
	}

	char line[MAX_LINE];

	while(fgets(line,sizeof(line),fp))
	{
		int len=strlen(line);
		if(len > 0 && line[len -1] == '\n')
		{
			line[len - 1] == '\0';
		}

		if(line[0] == '\0')
		{
			continue;
		}
		printf("Executing: %s\n",line);
		int ret=system(line);
		if(ret == -1)
		{
			perror("system");
			break;
		}
	}

	fclose(fp);
	return 0;
}
