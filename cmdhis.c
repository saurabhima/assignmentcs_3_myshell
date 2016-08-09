#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<termios.h>



static struct termios old, new;
char s[5][1000]={"one", "two hai ye","three to kamaal hai","four ki kya kahaun mai", "5"};



void initTermios(int echo)
{
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  new = old; /* make new settings same as old settings */
  new.c_lflag &= ~ICANON; /* disable buffered i/o */
  new.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
  tcsetattr(0, TCSANOW, &new); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void)
{
  tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo)
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

/* Read 1 character without echo */
char getch(void)
{
  return getch_(0);
}

/* Read 1 character with echo */
char getche(void)
{
  return getch_(1);
}


/*void main()
{
char ch1,ch2,ch3;
ch1=getch();
	if((int)ch1==27)
	{
		ch2=getch();
		ch3=getch();
		if(ch3=='A')
		{
			printf("up\n");
		}
		if(ch3=='B')
		{
			printf("down\n");
		}
	}
}*/

