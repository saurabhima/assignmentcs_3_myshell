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

#define MAX_STR_LENGTH 200

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

void print_string(FILE *ptr, char * pattern, int flag_invert,int flag_maxcount,int maxcount_num) {


    char str[MAX_STR_LENGTH];
    rewind(ptr);
    char *ret;
    int maxcounter=0;
    if(flag_invert==0)
    {while (fgets(str, MAX_STR_LENGTH, ptr)) {
        ret = strstr(str, pattern);
        if (ret != NULL && flag_maxcount==0)printf("%s", str);
        if (ret != NULL && flag_maxcount==1 && maxcounter<maxcount_num)
        	{
        	printf("%s", str);
        	maxcounter++;
        	}
    }
    }
    if(flag_invert==1)
    {while (fgets(str, MAX_STR_LENGTH, ptr)) {
        ret = strstr(str, pattern);
         if (ret == NULL && flag_maxcount==0)printf("%s", str);
        if (ret == NULL && flag_maxcount==1 && maxcounter<maxcount_num)
        	{
        	printf("%s", str);
        	maxcounter++;
        	}
    }
    }
}

void print_string_pat1(FILE *ptr, char * pattern, int flag_invert,int flag_maxcount,int maxcount_num) {

    char str[MAX_STR_LENGTH];
    rewind(ptr);
    char checkpat[MAX_STR_LENGTH];
    strcpy(checkpat, pattern);
    int maxcounter=0;
    char finalstr1[MAX_STR_LENGTH], finalstr2[MAX_STR_LENGTH];
    int x, y = 0, z = 0;
    int delimit = 0;
    for (x = 0; x < strlen(checkpat); x++) {
        if (checkpat[x] == '?') delimit = x;
    }
    char prevchar = checkpat[delimit - 1];

    for (x = 0; x < delimit - 1; x++) {
        finalstr1[y] = checkpat[x];
        y++;
        finalstr2[z] = checkpat[x];
        z++;
    }
    finalstr2[z++] = prevchar;
    for (x = delimit + 1; x <= strlen(checkpat); x++) {
        finalstr1[y] = checkpat[x];
        y++;
        finalstr2[z] = checkpat[x];
        z++;
    }
    //printf("\nDelimiter char-->%c", prevchar);
    //printf("\nPattern1-->%s", finalstr1);
    //printf("\nPattern2-->%s", finalstr2);

    char *ret1, *ret2;

    if(flag_invert==0)
    {while (fgets(str, MAX_STR_LENGTH, ptr)) {
        ret1 = strstr(str, finalstr1);
        ret2 = strstr(str, finalstr2);
        if ((ret1 != NULL || ret2 != NULL) && flag_maxcount==0)printf("%s", str);
        if ((ret1 != NULL || ret2 != NULL) && flag_maxcount==1 && maxcounter<maxcount_num)
        	{
        	printf("%s", str);
        	maxcounter++;
        	}
    }
    }
    if(flag_invert==1)
    {while (fgets(str, MAX_STR_LENGTH, ptr)) {
        ret1 = strstr(str, finalstr1);
        ret2 = strstr(str, finalstr2);
         if ((ret1 == NULL || ret1 == NULL) && flag_maxcount==0)printf("%s", str);
        if ((ret1 == NULL || ret1 == NULL) && flag_maxcount==1 && maxcounter<maxcount_num)
        	{
        	printf("%s", str);
        	maxcounter++;
        	}
    }
    }
        
  

}

print_string_pat3(FILE *ptr, char * pattern, int flag_invert,int flag_maxcount,int maxcount_num) {
    char str[MAX_STR_LENGTH];
    rewind(ptr);
    int maxcounter=0;
    char checkpat[MAX_STR_LENGTH];
    strcpy(checkpat, pattern);
    char finalstr1[MAX_STR_LENGTH], finalstr2[10][MAX_STR_LENGTH];
    int x, y = 0, z = 0;
    int delimit = 0;
    for (x = 0; x < strlen(checkpat); x++) {
        if (checkpat[x] == '+') delimit = x;
    }
    char prevchar = checkpat[delimit - 1];
    int a;
    for (a = 0; a < 10; a++) {
        y = 0;
        for (x = 0; x < delimit; x++) {
            finalstr2[a][y] = checkpat[x];
            y++;
        }
        for (x = 0; x < a; x++) {
            finalstr2[a][y] = prevchar;
            y++;
        }
        for (x = delimit + 1; x <= strlen(checkpat); x++) {
            finalstr2[a][y] = checkpat[x];
            y++;
        }

        //printf("\nPattern2-->%s", finalstr2[a]);
    }
    char *ret2[10];
    if(flag_invert==0)
    {while (fgets(str, MAX_STR_LENGTH, ptr)) {
       
         for (a = 0; a < 10; a++) {
            ret2[a] = strstr(str, finalstr2[a]);
            if (ret2[a] != NULL && flag_maxcount==0)
            	{
            	printf("%s", str);
            	break;
            	}
        	if (ret2[a]!= NULL  && flag_maxcount==1 && maxcounter<maxcount_num)
        	{
        	printf("%s", str);
        	maxcounter++;
        	break;
        	}
          }
        }
    }
    
    if(flag_invert==1)
    {while (fgets(str, MAX_STR_LENGTH, ptr)) {
       
       for (a = 0; a < 10; a++) {
            ret2[a] = strstr(str, finalstr2[a]);
            if (ret2[a] == NULL && flag_maxcount==0)
            	{
            	printf("%s", str);
            	break;
            	}
        	if (ret2[a]== NULL  && flag_maxcount==1 && maxcounter<maxcount_num)
        	{
        	printf("%s", str);
        	maxcounter++;
        	break;
        	}
          }
        } 
    
    
    }

}

void print_string_pat2(FILE *ptr, char * pattern,int flag_invert,int flag_maxcount,int maxcount_num) {
    char str[MAX_STR_LENGTH];
    rewind(ptr);
    int maxcounter=0;
    char checkpat[MAX_STR_LENGTH];
    strcpy(checkpat, pattern);
    char finalstr1[MAX_STR_LENGTH], finalstr2[10][MAX_STR_LENGTH];
    int x, y = 0, z = 0;
    int delimit = 0;
    for (x = 0; x < strlen(checkpat); x++) {
        if (checkpat[x] == '*') delimit = x;
    }
    char prevchar = checkpat[delimit - 1];

    for (x = 0; x < delimit - 1; x++) {
        finalstr1[y] = checkpat[x];
        y++;
    }
    for (x = delimit + 1; x <= strlen(checkpat); x++) {
        finalstr1[y] = checkpat[x];
        y++;
    }
    //printf("\nDelimiter char-->%c", prevchar);
    //printf("\nPattern1-->%s", finalstr1);
    int a;
    for (a = 0; a < 10; a++) {
        y = 0;
        for (x = 0; x < delimit; x++) {
            finalstr2[a][y] = checkpat[x];
            y++;
        }
        for (x = 0; x < a; x++) {
            finalstr2[a][y] = prevchar;
            y++;
        }
        for (x = delimit + 1; x <= strlen(checkpat); x++) {
            finalstr2[a][y] = checkpat[x];
            y++;
        }

        //printf("\nPattern2-->%s", finalstr2[a]);
    }
    char *ret1, *ret2[10];
    /*while (fgets(str, MAX_STR_LENGTH, ptr)) {

        ret1 = strstr(str, finalstr1);
        if (ret1 != NULL) {
            printf("%s", str);

        }
        for (a = 0; a < 10; a++) {
            ret2[a] = strstr(str, finalstr2[a]);
            if (ret2[a] != NULL) {
                printf("%s", str);
                break;
            }
        }
    }*/
    
    if(flag_invert==0)
    {while (fgets(str, MAX_STR_LENGTH, ptr)) {
        ret1 = strstr(str, finalstr1);
        
        if (ret1 != NULL && flag_maxcount==0)printf("%s", str);
        if (ret1 != NULL  && flag_maxcount==1 && maxcounter<maxcount_num)
        	{
        	printf("%s", str);
        	maxcounter++;
        	}
         for (a = 0; a < 10; a++) {
            ret2[a] = strstr(str, finalstr2[a]);
            if (ret2[a] != NULL && flag_maxcount==0)
            	{
            	printf("%s", str);
            	break;
            	}
        	if (ret2[a]!= NULL  && flag_maxcount==1 && maxcounter<maxcount_num)
        	{
        	printf("%s", str);
        	maxcounter++;
        	break;
        	}
          }
        }
    }
    
    if(flag_invert==1)
    {while (fgets(str, MAX_STR_LENGTH, ptr)) {
       ret1 = strstr(str, finalstr1);
        if (ret1 == NULL && flag_maxcount==0)printf("%s", str);
        if (ret1 == NULL  && flag_maxcount==1 && maxcounter<maxcount_num)
        	{
        	printf("%s", str);
        	maxcounter++;
        	}
       for (a = 0; a < 10; a++) {
            ret2[a] = strstr(str, finalstr2[a]);
            if (ret2[a] == NULL && flag_maxcount==0)
            	{
            	printf("%s", str);
            	break;
            	}
        	if (ret2[a]== NULL  && flag_maxcount==1 && maxcounter<maxcount_num)
        	{
        	printf("%s", str);
        	maxcounter++;
        	break;
        	}
          }
        } 
    
    
    }

}

int check_pattern(char *pattern) {
    char *retval1, *retval2,*retval3;
    char *pt1 = "?";
    char *pt2 = "*";
    char *pt3 = "+";
    int retint;
    retval1 = strstr(pattern, pt1);
    retval2 = strstr(pattern, pt2);
    retval3 = strstr(pattern, pt3);
    if (retval1 == NULL && retval2 == NULL && retval3 == NULL) {
        retint = 1;
    } else
        if (retval1 = !NULL && retval2 == NULL && retval3 == NULL) {
        retint = 2;

    } else
        if (retval1 == NULL && retval2 != NULL && retval3 == NULL) {
        retint = 3;

    }
    else
        if (retval1 == NULL && retval2 == NULL && retval3 != NULL) {
        retint = 4;

    }
    
    return (retint);
}

int main(int argc, char *argv[]) {
    char *command, *file, *option, *pattern;
    FILE *fileptr1;
    char str[MAX_STR_LENGTH];
    //system("clear");
    int argno = argc;
    if (argno < 3) {
        printf("\nArguement Error..Please Check\n");
        exit(0);
    }

    switch (argno) {
        case 3:
        {
            pattern = argv[argno-2];
            file = argv[argno-1];
            int ptcheck = check_pattern(pattern);
            //printf("\n%s", pattern);
            fileptr1 = fopen(file, "r");
            if (fileptr1 == NULL) {
                fputs("File does not exist", stderr);
                exit(1);
                break;
            }
            int lines1 = count_lines(fileptr1);
            printf("No of LInes in File 1-->%d\n", lines1);
            if (ptcheck == 1)print_string(fileptr1, pattern,0,0,0);
            if (ptcheck == 2)print_string_pat1(fileptr1, pattern,0,0,0);
           
            if (ptcheck == 3)print_string_pat2(fileptr1, pattern,0,0,0);
             if (ptcheck == 4)print_string_pat3(fileptr1, pattern,0,0,0);
            fclose(fileptr1);
            break;
        }
        
        case 4:
        {
            pattern = argv[argno-2];
            file = argv[argno-1];
            int ptcheck = check_pattern(pattern);
            //printf("\n%s", pattern);
            int flag_invert=0,flag_maxcount=0,maxcount_num=0;
            fileptr1 = fopen(file, "r");
            if (fileptr1 == NULL) {
                fputs("File does not exist", stderr);
                exit(1);
                break;
            }
            int lines1 = count_lines(fileptr1);
            printf("No of LInes in File 1-->%d\n", lines1);
            char *flagv1="-v";
            char *flagv2="--inverted-match";
            char *flagm1="-m";
            char *flagm2="--max-count";
            if(strcmp(argv[1],flagv1)==0||strcmp(argv[1],flagv2)==0)flag_invert=1;
            printf("\nInvert Flag-->%d", flag_invert);
            if(strcmp(argv[1],flagm1)==0||strcmp(argv[1],flagm2)==0)
            {
            printf("\nIllegal Arguements");
            fclose(fileptr1);
            exit(0);
            flag_maxcount=1;
            maxcount_num=atoi(argv[2]);
            }
            printf("\nMax Count Flag-->%d", flag_maxcount);
            if (ptcheck == 1)print_string(fileptr1, pattern,flag_invert,flag_maxcount,maxcount_num);
            if (ptcheck == 2)print_string_pat1(fileptr1, pattern,flag_invert,flag_maxcount,maxcount_num);
            if (ptcheck == 3)print_string_pat2(fileptr1, pattern,flag_invert,flag_maxcount,maxcount_num);
             if (ptcheck == 4)print_string_pat3(fileptr1, pattern,flag_invert,flag_maxcount,maxcount_num);
            fclose(fileptr1);
            break;
        }
        case 5:
        {
            pattern = argv[argno-2];
            file = argv[argno-1];
            int ptcheck = check_pattern(pattern);
            //printf("\n%s", pattern);
            int flag_invert=0,flag_maxcount=0,maxcount_num=0;
            fileptr1 = fopen(file, "r");
            if (fileptr1 == NULL) {
                fputs("File does not exist", stderr);
                exit(1);
                break;
            }
            int lines1 = count_lines(fileptr1);
            printf("No of LInes in File 1-->%d\n", lines1);
            char *flagv1="-v";
            char *flagv2="--inverted-match";
            char *flagm1="-m";
            char *flagm2="--max-count";
            if(strcmp(argv[1],flagv1)==0||strcmp(argv[1],flagv2)==0)
            {flag_invert=1;
             printf("\nIllegal Arguements");
             fclose(fileptr1);
             exit(0);
             }
            printf("\nInvert Flag-->%d", flag_invert);
            if(strcmp(argv[1],flagm1)==0||strcmp(argv[1],flagm2)==0)
            {
            flag_maxcount=1;
            maxcount_num=atoi(argv[2]);
            }
            printf("\nMax Count Flag-->%d", flag_maxcount);
            if (ptcheck == 1)print_string(fileptr1, pattern,flag_invert,flag_maxcount,maxcount_num);
            if (ptcheck == 2)print_string_pat1(fileptr1, pattern,flag_invert,flag_maxcount,maxcount_num);
            if (ptcheck == 3)print_string_pat2(fileptr1, pattern,flag_invert,flag_maxcount,maxcount_num);
             if (ptcheck == 4)print_string_pat3(fileptr1, pattern,flag_invert,flag_maxcount,maxcount_num);
            fclose(fileptr1);
            break;
        }
        
        case 6:
        {
            pattern = argv[argno-2];
            file = argv[argno-1];
            int ptcheck = check_pattern(pattern);
            //printf("\n%s", pattern);
            int flag_invert=0,flag_maxcount=0,maxcount_num=0;
            fileptr1 = fopen(file, "r");
            if (fileptr1 == NULL) {
                fputs("File does not exist", stderr);
                exit(1);
                break;
            }
            int lines1 = count_lines(fileptr1);
            printf("No of LInes in File 1-->%d\n", lines1);
            char *flagv1="-v";
            char *flagv2="--inverted-match";
            char *flagm1="-m";
            char *flagm2="--max-count";
            if(strcmp(argv[1],flagv1)==0||strcmp(argv[1],flagv2)==0)
            {flag_invert=1;
             if(strcmp(argv[2],flagm1)==0||strcmp(argv[2],flagm2)==0)
            {
            flag_maxcount=1;
            maxcount_num=atoi(argv[3]);
            }
            }
            printf("\nInvert Flag-->%d", flag_invert);
            if(strcmp(argv[1],flagm1)==0||strcmp(argv[1],flagm2)==0)
            {
            flag_maxcount=1;
            maxcount_num=atoi(argv[2]);
            if(strcmp(argv[3],flagv1)==0||strcmp(argv[3],flagv2)==0)
            {flag_invert=1;
            }
            
            }
            printf("\nMax Count Flag-->%d", flag_maxcount);
            if (ptcheck == 1)print_string(fileptr1, pattern,flag_invert,flag_maxcount,maxcount_num);
            if (ptcheck == 2)print_string_pat1(fileptr1, pattern,flag_invert,flag_maxcount,maxcount_num);
            if (ptcheck == 3)print_string_pat2(fileptr1, pattern,flag_invert,flag_maxcount,maxcount_num);
             if (ptcheck == 4)print_string_pat3(fileptr1, pattern,flag_invert,flag_maxcount,maxcount_num);
            fclose(fileptr1);
            break;
        }
        
        default:
        {
            break;
        }

    }

    return (0);
}



