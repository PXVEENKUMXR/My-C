#include<stdio.h>
#include<time.h>
#include<sys/stat.h>
#include<sys/types.h>

int main()
{
	char dir[100];
	time_t now = time(NULL);
	struct tm *t = localtime(&now);

	strftime(dir,sizeof(dir),"%Y-%m-%d",t);

	if(mkdir(dir,0755) == -1)
	{
		perror("mkdir");
		return 1;
	}
	printf("Directory '%s' created successfully\n",dir);
	return 0;
}
