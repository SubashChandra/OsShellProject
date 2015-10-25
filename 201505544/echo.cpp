#include "headers.h"


void replaceEnv(char str[],char temp[])
{
	int index=0; //for temp
	int i=0;
	int sinQuoteFlag=0;
	char env[50];
	int envIndex=0;
	while(i<strlen(str))
	{
		if(str[i]==39) //toggle flag if it is a single quote
		{
			sinQuoteFlag=(sinQuoteFlag+1)%2;
		}

		//only replace $env if it is outside a single quote
		if(str[i]=='$' && sinQuoteFlag==0) //once $ is visited, get the next string till space nd do getenv()
		{
			i++;
			while(i<strlen(str) && str[i]!=' ' && str[i]!='"')
			{
				env[envIndex]=str[i];
				envIndex++;
				i++;
			}
			env[envIndex]='\0';
			//printf("%s**\n",env);
			char *ans=getenv(env);
			if(ans!=NULL) //if a global var exists, copy it to the string
			{
				int j=0;
				while(j<strlen(ans))
				{
					temp[index]=ans[j];
					index++;
					j++;
				}
	

				if(i<strlen(str) && str[i]==' ') //if there was space after $var
				{
					temp[index]=str[i];
					index++;
					i++;
				}
				
			}

		}
		else
		{
			temp[index]=str[i];
			index++;
			i++;
		}
	}
}


void runEcho(char str[])
{
	if(fork()==0) //child
	{
		char **c1;
		c1=(char**)malloc(sizeof(char*)*10);
		int j;
		for(j=0;j<10;j++)
		{
			c1[j]=(char*)malloc(sizeof(char)*10000);
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
	else //parent
	{
		wait(NULL);
	}
}

void execEcho(char str[])
{
	char temp[10000];
	replaceEnv(str,temp); //temp has the env vars replaced if it exists
	removeQuotes(temp);
	runEcho(temp);//using execvp
	memset(&temp[0],0,strlen(temp));
}
