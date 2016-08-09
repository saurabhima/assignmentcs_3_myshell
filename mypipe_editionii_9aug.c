#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <sys/types.h> 
#include <sys/stat.h>
#include <unistd.h>
#include<string.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{

printf("\n%s",argv[1]);
char *substring = (char*) malloc(1024*sizeof(char));

strcpy(substring,argv[1]);


char *command[256];
char *token;
int counter=0;
token=strtok(substring,"|");

command[0]=token;
counter++;
printf("\nFirst Command-->%s\n",command[0]);
while(token!=NULL)
{ 
  // printf("%s\n",a[k]);
   token=strtok(NULL,"|");

command[counter]=token;
printf("\nNext Command-->%s\n",command[counter]);
counter++;

} 
  char temp[100];
  int i=0;
  int   p[2];
  pid_t pid;
  int   fd_in = 0;

  while (command[i]!= NULL)
    {
      pipe(p);
      if ((pid = fork()) == -1)
        {
          exit(EXIT_FAILURE);
        }
      else if (pid == 0)
        {
          dup2(fd_in, 0); //change the input according to the old one 
          if ((command[i+1]) != NULL)
          dup2(p[1], 1);
          close(p[0]);
         
          if(strstr(command[i], "my") == NULL) 
		{
 			system(command[i]);
	
                }
          else
		{
          		sprintf(temp,"./%s",command[i]);
			execlp(temp,command[i],NULL);
		}
          exit(EXIT_FAILURE);
        }
      else
        {
          wait(NULL);
          close(p[1]);
	
          fd_in = p[0]; //save the input for the next command
          i++;
        }
    }
}
