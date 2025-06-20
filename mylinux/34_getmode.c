#include <stdio.h>
#include <sys/stat.h>

void get_modes(mode_t mode) 
{
    char perms[10] = "---------";

    if (mode & S_IRUSR) perms[0] = 'r';
    if (mode & S_IWUSR) perms[1] = 'w';
    if (mode & S_IXUSR) perms[2] = 'x';

    if (mode & S_IRGRP) perms[3] = 'r';
    if (mode & S_IWGRP) perms[4] = 'w';
    if (mode & S_IXGRP) perms[5] = 'x';

    if (mode & S_IROTH) perms[6] = 'r';
    if (mode & S_IWOTH) perms[7] = 'w';
    if (mode & S_IXOTH) perms[8] = 'x';

    printf("Permissions: %s\n", perms);
}

int main() 
{
    struct stat st;

    if (stat("pk.txt", &st) == -1) 
    {
        perror("stat");
        return 1;
    }

    get_modes(st.st_mode);

    return 0;
}

