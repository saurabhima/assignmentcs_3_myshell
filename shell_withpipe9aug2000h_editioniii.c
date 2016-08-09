#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
//#include<ncurses.h>
#include<termios.h>
#include <unistd.h>

#define MAX_COMMAND_SZ 100
#define MAX_HISTORY_COUNT 20

char command_history[MAX_HISTORY_COUNT][100];
int command_count = 0;
static struct termios prev, next;

void initTermios(int echo) {
    tcgetattr(0, &prev); /* grab prev terminal i/o settings */
    next = prev; /* make next settings same as prev settings */
    next.c_lflag &= ~ICANON; /* disable buffered i/o */
    next.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
    tcsetattr(0, TCSANOW, &next); /* use these next terminal i/o settings now */
}

/* Restore prev terminal i/o settings */
void resetTermios(void) {
    tcsetattr(0, TCSANOW, &prev);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo) {
    char ch;
    initTermios(echo);
    ch = getchar();
    resetTermios();
    return ch;
}

/* Read 1 character without echo */
char getch(void) {
    return getch_(0);
}

/* Read 1 character with echo */
char getche(void) {
    return getch_(1);
}

int main(int argc, char **argv) {
    char command[100];
    int pipe_flag = 0;
    int x = 0;
    char ch;
    char path[1024];
    getcwd(path, sizeof (path));
    char execlp_str[100];
    pid_t pid;
    system("clear");
    printf("\nWelcome to Linux Shell 16CS60 IIT-KGP\n");
    printf("To Exit Press Esc+Enter\n");
    while (1) {
        x = 0;
        printf("Shell>");
        /*char char1,char2,char3;
        char1=getch();
        if((int)char1==27)
        {
                char2=getch();
                char3=getch();
                if(char3=='A')
                {
                        printf("\b\b\b\b\b\b");
                        printf("%s",command_history[command_count-1]);
                }
                if(char3=='B')
                {
                        printf("down\n");
                }
        //command[x]=char1;
        continue;
        }
        command[x++]=char1;
        printf("%c",char1);*/
        do {

            ch = getc(stdin);
            if (ch == 27) return (0);
            command[x] = ch;
            x++;
        } while (ch != '\n');
        command[x - 1] = '\0';
        //printf("\n%s", command);
        /*if(command_count==MAX_HISTORY_COUNT)
        {
        int st;
        for (st=0;st<command_count;st++)
        strcpy(command_history[st],command_history[st+1]);
        command_count--;
        }
        strcpy(command_history[command_count++],command);*/
        pid = fork();

        if (pid == 0) {
            const char delimiter[2] = " ";

            char pipe = '|';
            const char delimiter_pipe[2] = "|";
            char *initial_command, *token, *token_pipe;
            int count = 0;
            char parameter[50][100];
            char parameter_text[100];
            strcpy(parameter_text, "");
            char *current_command;
            if (strchr(command, pipe) != NULL) {
                //printf("Pipe found in command\n");
                pipe_flag = 1;
                token_pipe = strtok(command, delimiter_pipe);
                parameter[count++] = token_pipe;
                printf("\n%s", parameter[count]);
                              

                while (token != NULL) {

                    token_pipe = strtok(NULL, delimiter_pipe);
                    
                    if (token != NULL) {
                        strcpy(parameter[count], token_pipe);
                        printf("\n%s", parameter[count]);
                        count++;

                    }
                }

            
            //count--;
                initial_command = "mypipe";
                current_command = path;
            	//strcpy(current_command,path);
            	strcat(current_command, "/");
            	strcat(current_command, initial_command);
                char **argvpipe;
                strcpy(argvpipe[0], "mytail");
                printf("\nValue of COunt-->%i", count);
                argv = malloc((count + 2) * sizeof (char*));
                int i;
                argvpipe[0] = malloc(strlen("mypipe") * sizeof (char));
                for (i = 1; i <= count + 1; i++)
                    argv[i] = malloc(strlen(parameter[i - 1]) * sizeof (char));
                
                printf("\nValue of Argv[0]-->%s", argv[0]);
                argv[count + 1] = (char*) NULL;
                printf("\nVaule of argv%i-->%s", count + 1, argv[count + 1]);
                for (i = 1; i < count + 1; i++) {
                    strcpy(argv[i], parameter[i - 1]);
                    printf("\nValue of Argv[%i]-->%s", i, argv[i]);
                }

                argvpipe = malloc(4 * sizeof (char*));
                int i;
               
                argvpipe[1] = malloc(strlen(command) * sizeof (char));
                strcpy(argvpipe[0], "mypipe");
                strcpy(argvpipe[1], command);
                //printf("\nCOmmand line pipe Arguements-->%s\n",command);
                argvpipe[2] = (char*) NULL;
                if (execvp(current_command, argvpipe) == -1) printf("Execv is not working\n");
                free(argvpipe);
            }


                
                
             else {
                //token_pipe = strtok(command, delimiter_pipe);
                token = strtok(command, delimiter);
                initial_command = token;
                //printf("\n%s", initial_command);
                count = 0;

                strcpy(parameter_text, "");

                while (token != NULL) {

                    token = strtok(NULL, delimiter);
                    count++;
                    if (token != NULL) {
                        strcpy(parameter[count - 1], token);
                        strcat(parameter_text, token);
                        strcat(parameter_text, " ");

                        printf("\n%s", parameter[count - 1]);

                    }
                }
            }
            count--;
            //printf("\n%i",count);
            //printf("\n%s",parameter_text);
            int t;
            current_command = path;
            //strcpy(current_command,path);
            strcat(current_command, "/");
            strcat(current_command, initial_command);
            //printf("\n%s",current_command);
            //printf("\nThis is Child Process\n");
           
            if (strcmp(initial_command, "mypwd") == 0) {

                //printf("\n%s",current_command);
                static char *argv[] = {"mypwd", NULL};
                if (execvp(current_command, argv) == -1) printf("Execv is not working\n");
                
            }
            else

            if (strcmp(initial_command, "myps") == 0) {

                //printf("\n%s",current_command);
                static char *argv[] = {"myps", NULL};
                if (execvp(current_command, argv) == -1) printf("Execv is not working\n");
                
            } else
                if (strcmp(initial_command, "myls") == 0) {

                //printf("\n%s",current_command);
                static char *argv[] = {"myls", NULL};
                if (execvp(current_command, argv) == -1) printf("Execv is not working\n");
                
            } else
                if (strcmp(initial_command, "mytail") == 0) {

                //printf("\n%s",current_command);
                char **argv;
                printf("\nValue of COunt-->%i", count);
                argv = malloc((count + 3) * sizeof (char*));
                int i;
                argv[0] = malloc(strlen("mytail") * sizeof (char));
                for (i = 1; i <= count + 1; i++)
                    argv[i] = malloc(strlen(parameter[i - 1]) * sizeof (char));
                strcpy(argv[0], "mytail");
                printf("\nValue of Argv[0]-->%s", argv[0]);
                argv[count + 1] = (char*) NULL;
                printf("\nVaule of argv%i-->%s", count + 1, argv[count + 1]);
                for (i = 1; i < count + 1; i++) {
                    strcpy(argv[i], parameter[i - 1]);
                    printf("\nValue of Argv[%i]-->%s", i, argv[i]);
                }


                
                if (execvp(current_command, argv) == -1) printf("Execv is not working\n");
                
            }
            else
                if (strcmp(initial_command, "mycd") == 0) {

                //printf("\n%s",current_command);
                char **argv;
                printf("\nValue of COunt-->%i", count);
                argv = malloc((count + 3) * sizeof (char*));
                int i;
                argv[0] = malloc(strlen("mytail") * sizeof (char));
                for (i = 1; i <= count + 1; i++)
                    argv[i] = malloc(strlen(parameter[i - 1]) * sizeof (char));
                strcpy(argv[0], "mycd");
                printf("\nValue of Argv[0]-->%s", argv[0]);
                argv[count + 1] = (char*) NULL;
                printf("\nVaule of argv%i-->%s", count + 1, argv[count + 1]);
                for (i = 1; i < count + 1; i++) {
                    strcpy(argv[i], parameter[i - 1]);
                    printf("\nValue of Argv[%i]-->%s", i, argv[i]);
                }


                
                if (execvp(current_command, argv) == -1) printf("Execv is not working\n");
                
            }
            else
                if (strcmp(initial_command, "mymkdir") == 0) {

                printf("\n%s", current_command);
                char **argv;
                printf("\nValue of COunt-->%i", count);
                argv = malloc((count + 3) * sizeof (char*));
                int i;
                argv[0] = malloc(strlen("mytail") * sizeof (char));
                for (i = 1; i <= count + 1; i++)
                    argv[i] = malloc(strlen(parameter[i - 1]) * sizeof (char));
                strcpy(argv[0], "mymkdir");
                printf("\nValue of Argv[0]-->%s", argv[0]);
                argv[count + 1] = (char*) NULL;
                printf("\nVaule of argv%i-->%s", count + 1, argv[count + 1]);
                for (i = 1; i < count + 1; i++) {
                    strcpy(argv[i], parameter[i - 1]);
                    printf("\nValue of Argv[%i]-->%s", i, argv[i]);
                }


                
                if (execvp(current_command, argv) == -1) printf("Execv is not working\n");
                
            }
            else
                if (strcmp(initial_command, "mymv") == 0) {

                printf("\n%s", current_command);
                char **argv;
                printf("\nValue of COunt-->%i", count);
                argv = malloc((count + 3) * sizeof (char*));
                int i;
                argv[0] = malloc(strlen("mytail") * sizeof (char));
                for (i = 1; i <= count + 1; i++)
                    argv[i] = malloc(strlen(parameter[i - 1]) * sizeof (char));
                strcpy(argv[0], "mymv");
                printf("\nValue of Argv[0]-->%s", argv[0]);
                argv[count + 1] = (char*) NULL;
                printf("\nVaule of argv%i-->%s", count + 1, argv[count + 1]);
                for (i = 1; i < count + 1; i++) {
                    strcpy(argv[i], parameter[i - 1]);
                    printf("\nValue of Argv[%i]-->%s", i, argv[i]);
                }


                
                if (execvp(current_command, argv) == -1) printf("Execv is not working\n");
                
            }
            else
                if (strcmp(initial_command, "myrm") == 0) {

                printf("\n%s", current_command);
                char **argv;
                printf("\nValue of COunt-->%i", count);
                argv = malloc((count + 3) * sizeof (char*));
                int i;
                argv[0] = malloc(strlen("mytail") * sizeof (char));
                for (i = 1; i <= count + 1; i++)
                    argv[i] = malloc(strlen(parameter[i - 1]) * sizeof (char));
                strcpy(argv[0], "myrm");
                printf("\nValue of Argv[0]-->%s", argv[0]);
                argv[count + 1] = (char*) NULL;
                printf("\nVaule of argv%i-->%s", count + 1, argv[count + 1]);
                for (i = 1; i < count + 1; i++) {
                    strcpy(argv[i], parameter[i - 1]);
                    printf("\nValue of Argv[%i]-->%s", i, argv[i]);
                }


                
                if (execvp(current_command, argv) == -1) printf("Execv is not working\n");
                
            }
            else
                if (strcmp(initial_command, "mygrep") == 0) {

                //printf("\n%s",current_command);
                char **argv;
                printf("\nValue of Count-->%i", count);
                argv = malloc((count + 3) * sizeof (char*));
                int i;
                argv[0] = malloc(strlen("mytail") * sizeof (char));
                for (i = 1; i <= count + 1; i++)
                    argv[i] = malloc(strlen(parameter[i - 1]) * sizeof (char));
                strcpy(argv[0], "mytail");
                printf("\nValue of Argv[0]-->%s", argv[0]);
                argv[count + 1] = (char*) NULL;
                printf("\nVaule of argv%i-->%s", count + 1, argv[count + 1]);
                for (i = 1; i < count + 1; i++) {
                    strcpy(argv[i], parameter[i - 1]);
                    printf("\nValue of Argv[%i]-->%s", i, argv[i]);
                }


                
                if (execvp(current_command, argv) == -1) printf("Execv is not working\n");
                
            }
            else
            {
            	system(command);
            	
            }
            //printf("\nPrinting outside If Loop\n");
            exit(0);

        } else

            if (pid != 0) {
            waitpid(pid, 0, 0);
            //printf("\nThis is Parent Process\n");

        }








    }

    return (0);
}
