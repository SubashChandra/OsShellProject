//for auxillary functions that can be implemented using execvp 
// and shell built in's
#include "headers.h"


void execPwd()
{
	char temp[1000];
	getcwd(temp,1000);
	printf("%s\n",temp);
}


void execCd(char str[])
{
	char *token;
	token=strtok(str," "); //token has first arg
	token=strtok(NULL," "); //token has second arg
	if(chdir(token)==-1)
	{
		printf("myerror: change dir failed\n");
	}
}


//for executing /bin commands
void execCommand(char str[])
{
	if(fork()==0) //use child to execute ls
	{
		char **c1;
		c1=(char**)malloc(sizeof(char*)*10);
		int j;
		for(j=0;j<10;j++)
		{
			c1[j]=(char*)malloc(sizeof(char)*100);
		}
		char *token;
		token=strtok(str," ");
		j=0;
		while(token)
		{	
			c1[j]=token;
			token=strtok(NULL," ");
			j++;
		}
		c1[j]=NULL;
		execvp(c1[0],c1);
	}
	else
		wait(NULL);

}
