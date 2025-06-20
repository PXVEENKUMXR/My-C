#include<stdio.h>
#include<sys/stat.h>
#include<time.h>

int main()
{
	const char *file = "shravya.txt";
	struct stat st;
	if(stat(file,&st) != 0)
	{
		perror("stat");
		return 1;
	}
	printf("Timestamp of '%s' is %s",file,ctime(&st.st_mtime));
	return 0;
}
