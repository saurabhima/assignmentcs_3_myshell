#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <ctype.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>

#include <stdint.h>

int main(int argc, char *argv[])
 {

    

    DIR *d;
    struct dirent *dir;
    struct stat mystat;
    char buf[512];
    struct passwd *pw;
    struct group *gr;

    if (argc == 2) {
        d = opendir(argv[1]);
    } else {
        d = opendir(".");
    }

    if (d) {
        while ((dir = readdir(d)) != NULL) {
            sprintf(buf, "%s/%s", argv[1], dir->d_name);
            //printf("%s\n",buf);
            stat(buf, &mystat);
            pw = getpwuid(mystat.st_uid);
            gr = getgrgid(mystat.st_gid);

            printf((S_ISDIR(mystat.st_mode)) ? "d" : "-");
            printf((mystat.st_mode & S_IRUSR) ? "r" : "-");
            printf((mystat.st_mode & S_IWUSR) ? "w" : "-");
            printf((mystat.st_mode & S_IXUSR) ? "x" : "-");
            printf((mystat.st_mode & S_IRGRP) ? "r" : "-");
            printf((mystat.st_mode & S_IWGRP) ? "w" : "-");
            printf((mystat.st_mode & S_IXGRP) ? "x" : "-");
            printf((mystat.st_mode & S_IROTH) ? "r" : "-");
            printf((mystat.st_mode & S_IWOTH) ? "w" : "-");
            printf((mystat.st_mode & S_IXOTH) ? "x" : "-");
            int size = (int) mystat.st_size;
            printf("%d", size);
            //printf("%llu",mystat->st_size);
            //printf(" %-8.8s ",mystat.st_size);
            //printf(" %-8.8s", pw->pw_name);
            //printf("%u", pw->pw_name);
            //printf("%u", gr->gr_name);



            printf(" %s\n", dir->d_name);
            //printf("%s\t", dir->d_name);
        }

        closedir(d);
        printf("\n");
    }


    return (0);
}
