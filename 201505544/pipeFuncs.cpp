#include "headers.h"

//includes multtlevel pipe exec func nad otehr auxilary func

int hasPipe(char str[])
{
	int i,n;
	i=0;
	n=strlen(str);

	while(i<n)
	{
		if(str[i]=='|')
		{
			return 1;
		}
		i++;
	}
	return 0;
}

int pipeCount(char str[])
{
	int i,n,count=0;
	i=0;
	n=strlen(str);

	while(i<n)
	{
		if(str[i]=='|')
		{
			count++;
		}
		i++;
	}
	return count;
}

void executePipe(vector<Cmdnodeptr> v, int n)
{
	if(fork()==0) //cchild
	{
		int fd[2];
		int status[n];
		int i;
		for(i = 0;i < n;i++)
		{
			pipe(fd);
			if(fork() != 0)// Parent 
			{

				close(fd[1]);
				dup2(fd[0],0);
				close(fd[0]);

				wait(&status[i]);
				char **c1;
				c1=(char**)malloc(sizeof(char*)*10);
				int j;
				for(j=0;j<10;j++)
				{
					c1[j]=(char*)malloc(sizeof(char)*100);
				}
				char *token;
				token=strtok(v[n-i-1]->str," ");
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
			else // Child 
			{
				if(i == n-1)
					exit(0);
				close(fd[0]);
				dup2(fd[1],1);
				close(fd[1]);

			}
		}
	}
	else //parent
	{
		wait(NULL);
	}
		

}
