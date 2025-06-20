#include<stdio.h>
#include<unistd.h>

int main()
{
	const char *oldname = "newname.txt";
	const char *newname = "shravya.txt";

	if(rename(oldname,newname) != 0)
	{
		perror("Error renaming file");
		return 1;
	}
	printf("File renamed successfully!\n");
	return 0;
}
