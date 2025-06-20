#include<stdio.h>
#include<unistd.h>

int main()
{
	const char *file = "delete.txt";
	if(unlink(file) != 0)
	{
		perror("Error deleting file");
		return 1;
	}

	printf("File deleted successfully!\n");
	return 0;
}
