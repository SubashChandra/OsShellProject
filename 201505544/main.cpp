#include "headers.h"


//global variables
char promptString[1000];



int main()
{
	//restore history if there is any
	restoreHistory();
	
	char str[10000],temp[10000];	
	//do a infinite loop of command prompt
	getcwd(promptString,1000);
	printf("%s### ",promptString);
	while(1)
	{
		scanf("%[^\n]",str);
		getchar();
		
		//everytime add current command to localbuffer 
		//nd print to the history file
		addToHist(str);
		printToFile();
		
		
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
		else if(strcmp(token,"history")==0)
		{
			execHistory(str);
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
				execExport(str);
			}
			
		}

		//watever falls through implies /bin commands, use execvp
		else 
		{
			execCommand(str);
		}
		
		memset(&str[0],0,strlen(str));
	
		getcwd(promptString,1000);
		printf("%s### ",promptString);

	}
	return 0;
}
