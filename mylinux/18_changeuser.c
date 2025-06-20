#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pwd.h>
#include<sys/stat.h>
#include<sys/types.h>

int main()
{
	const char *file = "shravya.txt";
	const char *username = "praveenkumar";
	struct passwd *pw= getpwnam(username);

	if(pw == NULL)
	{
		fprintf(stderr, "User '%s' not found\n",username);
		return 1;
	}

	uid_t uid= pw->pw_uid;
	gid_t gid= pw->pw_gid;

	if(chown(file,uid,gid) != 0)
	{
		perror("chown");
		return 1;
	}

	printf("Ownership of '%s' changed to use '%s' (UID: %d, GID : %d)\n",file,username,uid,gid);
	return 0;
}
