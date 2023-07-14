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
        printf("Fichiers dans le dossier output :\n");
        while ((dir = readdir(d)) != NULL)
        {
            if (dir->d_type == DT_REG)
            {
                printf("%s\n", dir->d_name);
            }
        }
        closedir(d);
    }
    return 0;
}
