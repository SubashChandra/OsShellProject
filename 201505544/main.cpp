#include "headers.h"


//global variables
char promptString[1000];

//to handle ctrl+c
void handler(int s)
{
	return;
}


int main()
{
	//handle control+c
	signal(SIGINT,handler);

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

		if(strcmp(str,"")==0) //empty string, ignore
		{
			getcwd(promptString,1000);
			printf("%s### ",promptString);
			//skip rest of the loop
			continue;
		}


		
		//everytime add current command to localbuffer 
		//nd print to the history file
		//only add to history if command is not "!!" or "!no"
		if(str[0]!='!')
		{
			addToHist(str);
			printToFile();
		}
		
		//if !! execute the last command, ie change current command from !! to last executed command
		if(strcmp(str,"!!")==0)
		{
			if(curIndex==0) //if first command executed
			{
				printf("error: no previous command\n");
				getcwd(promptString,1000);
				printf("%s### ",promptString);
				continue;
			}

			int ind=(startIndex+curSize-1)%capacity;
			memset(&str[0],0,strlen(str));
			strcpy(str,hist[ind]);
			//printf("%s**\n",str);
		}


		//if !no excute the command at no in history, so replace appropriately
		if(str[0]=='!')
		{
			int i=1;
			int cmdInd=0;
			while(i<strlen(str))
			{
				cmdInd=cmdInd*10+str[i]-'0';
				i++;
			}
			
			if(cmdInd>curSize) //handle out of bound issues
			{
				cmdInd=curSize;
			}
			int ind=(startIndex+cmdInd-1)%capacity;
			memset(&str[0],0,strlen(str));
			strcpy(str,hist[ind]);
				
		}
		
		strcpy(temp,str);
		char *token;
		token=strtok(temp," ");
		//if has pipe handle it
		
		if(hasPipe(str))
		{
			int n=pipeCount(str);
			char p[10] = "|";
			vector<Cmdnodeptr> v = parseStr(str,p);
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

		//implement echo
		else if(strcmp(token,"echo")==0)
		{
//			execEcho(str);
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
