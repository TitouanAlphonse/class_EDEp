#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#include <dirent.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    struct dirent *dir;
    DIR *d = opendir("./output"); 
    if (d)
    {
        printf("Fichiers supprimés :\n");
        while ((dir = readdir(d)) != NULL)
        {
            if (dir->d_type == DT_REG)
            {
                printf("%s\n", dir->d_name);
                char path[270];
                sprintf(path, "./output/%s", dir->d_name);
                remove(path);
            }
        }
        closedir(d);
    }
    return 0;
}
