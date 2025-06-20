#include<stdio.h>
#include<sys/stat.h>

int main()
{
	const char *file = "sample.txt";
	struct stat st;
	if(stat(file,&st) !=0)
	{
		perror("stat");
		return 1;
	}

	printf("Size of '%s': %ld bytes\n",file,st.st_size);
	return 0;
}
