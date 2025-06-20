#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define PATH_LEN 4096

int main(void)
{
	char cwd[PATH_LEN];

	if(getcwd(cwd,sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		return 1;
	}

	write(STDOUT_FILENO, "Currentt working directory : ",27);
	write(STDOUT_FILENO, cwd,strlen(cwd));
	write(STDOUT_FILENO,"\n",1);
	return 0;
}
