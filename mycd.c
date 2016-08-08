#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
#include<dirent.h>
#include<stdlib.h>

int main(int argc, char *argv[]) {

    //system("clear");
    int argno = argc;
    int check = 12;
    if (argno != 2) {


        printf("\nArguement Error..Please Check\n");
        exit(0);


    }
    if (argno == 2) {
        char *dirname = argv[1];

        check = chdir(dirname);
        if (check != 0) {
            perror(dirname);
            return 1;
        }
        //execlp("ls", "ls", (char *)NULL);


    }




    return (0);
}

