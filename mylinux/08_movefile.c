#include<stdio.h>
#include<unistd.h>

int main()
{
	const char *old = "direct1/file.txt";
	const char *new = "direct2/file.txt";

	if(rename(old,new) != 0 )
	{
		perror("Error moving file");
		return 1;
	}
	printf("File moved successfully from '%s' to '%s'\n",old,new);
	return 0;
}
