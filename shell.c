#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
//#include<ncurses.h>

#define MAX_COMMAND_SZ 100

int main(int argc, char **argv) {
    char command[100];
    int x=0;
    char ch;
    char path[1024];
    getcwd(path, sizeof(path)); 
    char execlp_str[100];
    pid_t pid;
    system("clear");
   	printf("\nWelcome to Linux Shell 16CS60 IIT-KGP\n");
   	printf("To Exit Press Esc+Enter\n");
   	while(1)
   	{
   	x=0;
   	printf("\nShell>");
   	//fgets (command, MAX_COMMAND_SZ, stdin);
   	do
   	{
   	ch=getc(stdin);
   	if(ch==27) return(0);
   	command[x]=ch;
	x++;   	
   	}while(ch!='\n');
   	command[x-1] = '\0';
   	//printf("\n%s",command);
   	pid = fork();
	
    if (pid == 0)
		{
		const char delimiter[2]=" ";
   	char *initial_command,*token;
    token = strtok(command, delimiter);
   	initial_command=token;
   	//printf("\n%s",initial_command);
   	int count=0;
   	char parameter[50][100];
   	char parameter_text[100];
   	strcpy(parameter_text,"");
   	char *current_command;
   	while( token != NULL ) 
   {
      
      token = strtok(NULL, delimiter);
      count++;
      if(token!=NULL)
      {
       strcpy(parameter[count-1],token);
       strcat(parameter_text,token);
       strcat(parameter_text," ");
       
       printf("\n%s",parameter[count-1]);
      
      }
   }
   	count--;
   	//printf("\n%i",count);
   	//printf("\n%s",parameter_text);
   	int t;
   	current_command=path;
   	//strcpy(current_command,path);
   	strcat(current_command,"/");
   	strcat(current_command,initial_command);
   	//printf("\n%s",current_command);
		printf("\nThis is Child Process\n");
    	if(strcmp(initial_command,"mypwd")==0)
   		{
 		  		
   		//printf("\n%s",current_command);
   		static char *argv[]={"mypwd",NULL};
        if(execvp(current_command,argv)==-1) printf("Execv is not working\n");
   		//execlp(current_command, current_command, (char *)NULL);
   		}
   		
   		if(strcmp(initial_command,"myps")==0)
   		{
 		  		
   		//printf("\n%s",current_command);
   		static char *argv[]={"myps",NULL};
        if(execvp(current_command,argv)==-1) printf("Execv is not working\n");
   		//execlp(current_command, current_command, (char *)NULL);
   		}
   		else
   		if(strcmp(initial_command,"myls")==0)
   		{
 		  		
   		//printf("\n%s",current_command);
   		static char *argv[]={"myls",NULL};
        if(execvp(current_command,argv)==-1) printf("Execv is not working\n");
   		//execlp(current_command, current_command, (char *)NULL);
   		}
   		else
   		if(strcmp(initial_command,"mytail")==0)
   		{
 		  		
   		//printf("\n%s",current_command);
   		char **argv;
    printf("\nValue of COunt-->%i",count);
    argv = malloc((count+3) * sizeof(char*));
    int i;
    argv[0] = malloc(strlen("mytail") * sizeof(char));
    for (i = 1; i <= count+1; i++)
    argv[i] = malloc(strlen(parameter[i-1]) * sizeof(char));
   	strcpy(argv[0],"mytail");
   	printf("\nValue of Argv[0]-->%s",argv[0]);
   	 argv[count+1]=(char*)NULL;
   		printf("\nVaule of argv%i-->%s",count+1,argv[count+1]);
   	for (i = 1; i < count+1; i++)
   		{strcpy(argv[i],parameter[i-1]);
        printf("\nValue of Argv[%i]-->%s",i,argv[i]);}
       
   		
   		//char **argv={"mytail",parameter};
        if(execvp(current_command,argv)==-1) printf("Execv is not working\n");
   		//execlp(current_command, current_command, (char *)NULL);
   		}
   		
   		else
   		if(strcmp(initial_command,"mycd")==0)
   		{
 		  		
   		//printf("\n%s",current_command);
   		char **argv;
    printf("\nValue of COunt-->%i",count);
    argv = malloc((count+3) * sizeof(char*));
    int i;
    argv[0] = malloc(strlen("mytail") * sizeof(char));
    for (i = 1; i <= count+1; i++)
    argv[i] = malloc(strlen(parameter[i-1]) * sizeof(char));
   	strcpy(argv[0],"mycd");
   	printf("\nValue of Argv[0]-->%s",argv[0]);
   	 argv[count+1]=(char*)NULL;
   		printf("\nVaule of argv%i-->%s",count+1,argv[count+1]);
   	for (i = 1; i < count+1; i++)
   		{strcpy(argv[i],parameter[i-1]);
        printf("\nValue of Argv[%i]-->%s",i,argv[i]);}
       
   		
   		//char **argv={"mytail",parameter};
        if(execvp(current_command,argv)==-1) printf("Execv is not working\n");
   		//execlp(current_command, current_command, (char *)NULL);
   		}
   		
   		else
   		if(strcmp(initial_command,"mymkdir")==0)
   		{
 		  		
   		printf("\n%s",current_command);
   		char **argv;
    printf("\nValue of COunt-->%i",count);
    argv = malloc((count+3) * sizeof(char*));
    int i;
    argv[0] = malloc(strlen("mytail") * sizeof(char));
    for (i = 1; i <= count+1; i++)
    argv[i] = malloc(strlen(parameter[i-1]) * sizeof(char));
   	strcpy(argv[0],"mymkdir");
   	printf("\nValue of Argv[0]-->%s",argv[0]);
   	 argv[count+1]=(char*)NULL;
   		printf("\nVaule of argv%i-->%s",count+1,argv[count+1]);
   	for (i = 1; i < count+1; i++)
   		{strcpy(argv[i],parameter[i-1]);
        printf("\nValue of Argv[%i]-->%s",i,argv[i]);}
       
   		
   		//char **argv={"mytail",parameter};
        if(execvp(current_command,argv)==-1) printf("Execv is not working\n");
   		//execlp(current_command, current_command, (char *)NULL);
   		}
   		
   		else
   		if(strcmp(initial_command,"mymv")==0)
   		{
 		  		
   		printf("\n%s",current_command);
   		char **argv;
    printf("\nValue of COunt-->%i",count);
    argv = malloc((count+3) * sizeof(char*));
    int i;
    argv[0] = malloc(strlen("mytail") * sizeof(char));
    for (i = 1; i <= count+1; i++)
    argv[i] = malloc(strlen(parameter[i-1]) * sizeof(char));
   	strcpy(argv[0],"mymv");
   	printf("\nValue of Argv[0]-->%s",argv[0]);
   	 argv[count+1]=(char*)NULL;
   		printf("\nVaule of argv%i-->%s",count+1,argv[count+1]);
   	for (i = 1; i < count+1; i++)
   		{strcpy(argv[i],parameter[i-1]);
        printf("\nValue of Argv[%i]-->%s",i,argv[i]);}
       
   		
   		//char **argv={"mytail",parameter};
        if(execvp(current_command,argv)==-1) printf("Execv is not working\n");
   		//execlp(current_command, current_command, (char *)NULL);
   		}
   		
   		else
   		if(strcmp(initial_command,"myrm")==0)
   		{
 		  		
   		printf("\n%s",current_command);
   		char **argv;
    printf("\nValue of COunt-->%i",count);
    argv = malloc((count+3) * sizeof(char*));
    int i;
    argv[0] = malloc(strlen("mytail") * sizeof(char));
    for (i = 1; i <= count+1; i++)
    argv[i] = malloc(strlen(parameter[i-1]) * sizeof(char));
   	strcpy(argv[0],"myrm");
   	printf("\nValue of Argv[0]-->%s",argv[0]);
   	 argv[count+1]=(char*)NULL;
   		printf("\nVaule of argv%i-->%s",count+1,argv[count+1]);
   	for (i = 1; i < count+1; i++)
   		{strcpy(argv[i],parameter[i-1]);
        printf("\nValue of Argv[%i]-->%s",i,argv[i]);}
       
   		
   		//char **argv={"mytail",parameter};
        if(execvp(current_command,argv)==-1) printf("Execv is not working\n");
   		//execlp(current_command, current_command, (char *)NULL);
   		}
    	printf("\nPrinting outside If Loop");
    	exit(0);
    	
    	}
    else
	    
    if (pid != 0)
		{
		waitpid(pid,0,0);
		printf("\nThis is Parent Process\n");
		
    	}
	     
      

       
   
   	
   	
   
   }
    
    return (0);
}
