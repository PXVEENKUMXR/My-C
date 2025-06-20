#include<stdio.h>
#include<unistd.h>

int main()
{
	const char *src = "shravya.txt";
	const char *linkname = "pk.txt";

	if(link(src,linkname) !=0)
	{
		perror("link");
		return 1;
	}

	printf("Hard link '%s' created for '%s'\n",linkname,src);
	return 0;
}
