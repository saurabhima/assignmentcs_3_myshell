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

//printf("%s\n",argv[1]);
char *substring = (char*) malloc(1024*sizeof(char));

strcpy(substring,argv[1]);
//printf("%s\n",substring);

char *a[100];
char *token;
int k=0;
token=strtok(substring,"|");
//printf("%s\n",token);
a[0]=token;
while(token!=NULL)
{ 
  // printf("%s\n",a[k]);
   token=strtok(NULL,"|");
//printf("%s\n",token);
k++;
a[k]=token;
} 
  char temp[100];
  int i=0;
  int   p[2];
  pid_t pid;
  int   fd_in = 0;

  while (a[i]!= NULL)
    {
      pipe(p);
      if ((pid = fork()) == -1)
        {
          exit(EXIT_FAILURE);
        }
      else if (pid == 0)
        {
          dup2(fd_in, 0); //change the input according to the old one 
          if ((a[i+1]) != NULL)
          dup2(p[1], 1);
          close(p[0]);
         
          if(strstr(a[i], "my") == NULL) 
		{
 			system(a[i]);
	
                }
          else
		{
          		sprintf(temp,"./%s",a[i]);
			execlp(temp,a[i],NULL);
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
