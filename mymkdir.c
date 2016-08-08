#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
#include<dirent.h>
#include<stdlib.h>

int main(int argc, char *argv[]) {

    system("clear");
    int argno = argc;
    if (argno < 2) {


        printf("\nArguement Error..Please Check\n");
        exit(0);


    }
    if (argno == 2) {
        char *dirname = argv[1];
        if (dirname[0] != '/') {
            if (mkdir(dirname, 0777) == -1) {
                perror(dirname);
                exit(EXIT_FAILURE);

            } else {
                printf("\nDirectory Creattion Successful\n");
            }
        } else
            if (dirname[0] == '/') {
            if (mkdir(dirname, 0777) == -1) {
                perror(dirname);
                exit(EXIT_FAILURE);

            } else {
                printf("\nDirectory Creattion Successful\n");
            }
        }


    }

    if (argno > 2) {
        int count;
        char *dirname;
        for (count = 1; count < argno; count++) {

            dirname = argv[count];
            if (mkdir(dirname, 0777) == -1) {
                perror(dirname);
                //exit(EXIT_FAILURE);

            } else {
                printf("\nDirectory Creattion Successful\n");
            }
        }



    }


    return (0);
}






