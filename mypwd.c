#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <ctype.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
 {

    if (argc == 1) {


        char present_dir[200];

        if (getcwd(present_dir, sizeof (present_dir)) != NULL)
            printf("%s\n", present_dir);
        else
            printf("\nError in processing arguements");
    }
    else {
        printf("\nInvalid Arguements");
        exit(0);
    }

    return (0);
}
