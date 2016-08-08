
#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
#include<dirent.h>
#include<stdlib.h>
#include<ctype.h>
#include<unistd.h>

void recurse_dir(const char* dirname,int flag) {


    struct dirent *dirstruct, *dirsubstruct;
    DIR *dirptr = opendir(dirname);
    DIR *dirsubptr = NULL;
    FILE *fileptr1, *fileptr2;
    int counter = 0;
    char buffer[512] = {0};

    int i, dirnum = 22;
    char *filename;
    char *time_file;
    char *output_terminal;
    char *start = "/";
    char *proc = "proc";
    char *fd = "fd";
    char *status = "status";
    char *stat="stat";
    char *ter_ptr = "0";
    char *process_name,*final_proc_name;
    while ((dirstruct = readdir(dirptr)) != NULL) {
        dirnum = atoi(dirstruct->d_name);
        //printf("%i\t", dirnum);
        if (dirnum > 0) 
        {


            if (dirnum == getpid() || dirnum == getppid()) {
                filename = malloc(strlen(dirstruct->d_name) + 3 * (strlen(start)) + strlen(status) + strlen(proc) + 1);
                strcpy(filename, start);
                strcat(filename, proc);
                strcat(filename, start);
                strcat(filename, dirstruct->d_name);
                strcat(filename, start);
                //strcat(filename, fd);
                //strcat(filename, start);
                strcat(filename, status);
                //printf("%s\n",filename);
                fileptr1 = fopen(filename, "r");
                if (fileptr1 == NULL) {
                    fputs("File does not exist", stderr);
                    //exit(1);
                }
                char buffer[1000];
                char *ret = NULL, hold[1000];
                while (fgets(buffer, 100, fileptr1)) {

                    if (strncmp(buffer, "Name:", 5) != 0)
                        continue;
                    process_name = buffer + 6;
                    while (isspace(*process_name)) ++process_name;
                    final_proc_name=malloc(strlen(process_name)+1);
                    strcpy(final_proc_name,process_name);
                    //printf("\n%s\n", process_name);
                }

                output_terminal = malloc(strlen(dirstruct->d_name) + 4 * (strlen(start)) + strlen(ter_ptr) + strlen(proc) + strlen(fd) + 1);
                strcpy(output_terminal, start);
                strcat(output_terminal, proc);
                strcat(output_terminal, start);
                strcat(output_terminal, dirstruct->d_name);
                strcat(output_terminal, start);
                strcat(output_terminal, fd);
                strcat(output_terminal, start);
                strcat(output_terminal, ter_ptr);
                //printf("%s\n",output_terminal);

                if ((i = readlink(output_terminal, hold, sizeof (hold) - 1)) != -1) {


                    hold[i] = '\0';
                    ret = strchr(hold, '/');
                    ret++;
                    ret = strchr(ret, '/');
                    ret++;
                    if (strcmp(ret, "null") == 0)
                        ret = NULL;
                }
                //printf("\n%s\n",ret);


                time_file = malloc(strlen(dirstruct->d_name) + 3 * (strlen(start)) + strlen(proc) +strlen(stat)+ 1);
                strcpy(time_file,"/proc/" );
                strcat(time_file, dirstruct->d_name);
                strcat(time_file, "/stat");
                fileptr2 = fopen(time_file, "r");
                if (fileptr2 == NULL) {
                    fputs("File does not exist", stderr);}
                    char charcheck;
                    int clock_rate = sysconf(_SC_CLK_TCK);
                    charcheck = fgetc(fileptr2);
                    int count = 0, k = 0;
                    char time_data[4][100];
                    int id[4], total = 0;
                    for(i=0;i<=16 && charcheck!=EOF;)
            		{
                    	if(charcheck==' ')
                   	 	{
                            i++;
                            if(i>=14)
                            {
                                    time_data[k][count]='\0';
                                    k++;
                                    count=0;
                            }
                    	}
                    if(i>=13 && i<=16)
                    time_data[k][count++]=charcheck;
                    charcheck=fgetc(fileptr2);
            		}
            for(i=0;i<=3;i++)
            {
                    sscanf(time_data[i],"%d",&id[i]);
                    total=total+id[i];
            }
            int h,m,s;
            total=total / clock_rate;
            h=total/60;
            m=(total%60);
            printf("%5d %8s%5s:%02d:%02d	%s", dirnum, (ret == NULL ? "?" : ret), "00", h, m, final_proc_name);
            free(final_proc_name);
            fclose(fileptr2);
            free(filename);
            free(output_terminal);
            free(time_file);
            
        	
                }
                
            
           
            }
            


        }

    

   	 fclose(fileptr1);

    closedir(dirptr);
}

int listpscurrent() {
    const char* directory = "/proc/";

    struct dirent *dirstruct;
    DIR *dirptr = opendir(directory);
    //int counter=0;
    if (dirptr == NULL) {
        printf("\nThis Directory does not exist");
        return 1;
    }
    closedir(dirptr);
    recurse_dir(directory,0);


    return (0);

}

int listpsall() {
    const char* directory = "/proc/";

    struct dirent *dirstruct;
    DIR *dirptr = opendir(directory);
    
    if (dirptr == NULL) {
        printf("\nThis Directory does not exist");
        return 1;
    }
    closedir(dirptr);
    recurse_dir(directory,1);


    return (0);

}


int path_is_directory(const char* path) {
    struct stat s_buf;

    if (stat(path, &s_buf))
        return 0;

    return S_ISDIR(s_buf.st_mode);
}

int main(int argc, char *argv[]) {

    int argcount = argc;

    if (argcount == 1) {
        printf("\nProccess list for Current User\n");
        listpscurrent();
    } else
        if (argcount == 2 && strcmp(argv[1], "-a") == 0) {
        printf("\nProccess list for All User\n");
        //listpsall();
    } else {
        printf("\nIllegal Arguements, Please Check");
        exit(0);
    }


    return (0);

}
