#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
#include<stdlib.h>

int main(int argc, char *argv[]) {
    system("clear");
    if (argc < 3) {
        fputs("\nInvalid number of arguements\n", stderr);
        exit(1);
    }


    char *oldfile, *newfile;
    oldfile = argv[1];
    newfile = argv[2];
    printf("\n%s", oldfile);
    printf("\n%s", newfile);
    FILE *fileptr1;
    fileptr1 = fopen(oldfile, "r");
    if (fileptr1 == NULL) {

        fclose(fileptr1);
        int check = rename(oldfile, newfile);
        if (check != 0) {
            perror(newfile);
            exit(EXIT_FAILURE);
        }
        return (0); //exit(1);
    }

    fclose(fileptr1);
    int check = rename(oldfile, newfile);
    if (check != 0) {
        perror(newfile);
        exit(EXIT_FAILURE);
    }

    return (0);
}

