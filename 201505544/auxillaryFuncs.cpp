//for auxillary functions that can be implemented using execvp 
// and shell built in's
#include "headers.h"

void removeQuotes(char val[])
{
	int i=0;
	int index=0;
	while(i<strlen(val))
	{
		if(val[i]==39 || val[i]=='"')
		{
			i++;
		}
		else
		{
			val[index]=val[i];
			i++;
			index++;
		}
	}
	val[index]='\0';
}



void execExport(char str[])
{
	char name[50];
	char val[50];
	int i=0;
	int flag=0;
	while(i<strlen(str))
	{
		if(str[i]=='=')
			flag=1;
		i++;
	}

	if(flag==0)
	{
		printf("error: invalid command\n");
		return;
	}

	char *token;
	token=strtok(str," "); //take off history string from str
	token=strtok(NULL,"=");
	strcpy(name,token); //get name of var
	token=strtok(NULL,"=");
	strcpy(val,token); //get val of var
	removeQuotes(val);
	//printf("%s %s check\n",name,val);	
	int ans=setenv(name,val,1);
	//printf("status: %d\n",ans);
}


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
		int eno=execvp(c1[0],c1);
		if(eno==-1)
		{
			printf("error: invalid command\n");
		}
	}
	else
		wait(NULL);

}
