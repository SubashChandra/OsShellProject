#include "headers.h"


//global variables
char promptString[1000];
queue<string> hist[100]; //local history bffer
int curIndex=0; //curIndex for the histBuffer

void addToHist(char str[])
{
	char temp[1000];
	sprintf(temp,"%s\n",str);
	//printf("###%s",temp); 
	
	strcpy(hist[curIndex],temp);
	


}

	


int main()
{
	//do a infinite loop of command prompt
	char str[10000],temp[10000];	
	getcwd(promptString,1000);
	printf("%s# ",promptString);
	while(1)
	{
		scanf("%[^\n]",str);
		//everytime add current command to localbuffer 
		//nd add to the history file
		addToHist(str);
		getchar();
		strcpy(temp,str);
		char *token;
		token=strtok(temp," ");
		//if has pipe handle it
		if(hasPipe(str))
		{
			int n=pipeCount(str);
			vector<Cmdnodeptr> v = parseStr(str,"|");
			executePipe(v,n+1);
		}

		//use and else if for input nd output redirection
		/*else if(hasRedtn(str))
		{

		}*/

		else if(!strcmp(str,"exit"))
		{
			exit(0);
		}

		//implement local history
		else if(!strcmp(str,"history"))
		{

				
		}
		//if any of the builtins
		else if((strcmp(token,"cd")==0) || (strcmp(token,"pwd")==0) || (strcmp(token,"export")==0))
		{
			if(strcmp(token,"cd")==0)
			{
				execCd(str);
			}
			else if(strcmp(token,"pwd")==0)
			{
				execPwd();
			}
			if(strcmp(token,"export")==0)
			{
				printf("export here\n");
			}
			
		}

		//watever falls through implies /bin commands, use execvp
		else 
		{
			execCommand(str);
		}
		
		memset(&str[0],0,strlen(str));
	
		getcwd(promptString,1000);
		printf("%s# ",promptString);

	}
	return 0;
}
