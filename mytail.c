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

int count_lines(FILE *ptr) {
    rewind(ptr);
    char ch;
    int count = 0;
    while (1) {
        ch = getc(ptr);
        if (ch == EOF)break;
        if (ch == '\n')count++;
    }
    return (count);
}

int main(int argc, char *argv[])
 {

    system("clear");
    int ln = 0;
    char str[200];
    char lines[10], file[100];

    int count = 0;
    switch (argc) {
        case 3:
        {
            strcpy(lines, argv[1]);

            const char escp = '-';
            char *lines_c;
            lines_c = strchr(lines, escp);
            lines_c++;

            ln = atoi(lines_c);
            strcpy(file, argv[2]);
            FILE *fileptr1;
            fileptr1 = fopen(file, "r");
            if (fileptr1 == NULL) {

                fputs("File does not exist", stderr);
                exit(1);
                break;
            }
            int lines1 = count_lines(fileptr1);
            printf("No of LInes in File 1-->%d\n", lines1);
            if (ln > lines1) {
                printf("\n Input out of Bound");
                exit(0);
            }
            //char array_store[lines1 + 1][200];
            rewind(fileptr1);
            
	while (fgets(str, sizeof(str), fileptr1)) {
		++count;
                if (lines1 - count + 1 <= ln) {
                    printf("%s", str);
                }
	}	
	/*   do {

		//getline(char **lineptr, size_t *n, fileptr1);                
		//fscanf(fileptr1, "%s", str);
		while (fgets(str, sizeof(str), fileptr1)) {
        /* note that fgets don't strip the terminating \n, checking its
           presence would allow to handle lines longer that sizeof(line) 
        printf("%s", line); 
    }
                ++count;
                if (lines1 - count + 1 < ln) {
                    printf("%s\n", str);
                }

            } while (!feof(fileptr1));*/


            /*char str[200];
            long i = 0;
            int len=0;*/
            fclose(fileptr1);
            break;
        }





        default:
        {
            printf("\nError in processing arguements..Please Check");
            exit(0);
            break;
        }


    }

    return (0);
}

