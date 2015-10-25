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


		//if ! followed by some characters, repalce with first occurreence if match from history
		if(str[0]=='!' && strlen(str)>1)
		{
			if((str[1]>='a' && str[1]<='z') || (str[1]>='A' && str[1]<='Z'))
			{
				char temp[1000];
				int tempIndex=0;
				int i=1;
				while(i<strlen(str))
				{
					temp[tempIndex]=str[i];
					i++;
					tempIndex++;
				}
				temp[tempIndex]='\0';
				//printf("%s**\n",temp);

				//now we have partial string in temp
				//iterate over history nd set current command to the string that matches
				//if no match, set it to garbage so that error is given
				int index=startIndex;
				i=0;
				int found=0;
				while(i<curSize)
				{
					if(strstr(hist[index],temp)==NULL) //no match 
					{
						index=(index+1)%capacity;
					}
					else //match
					{
						found=1;
						break;
					}
					i++;
				}
				if(found==1)
				{
					strcpy(str,hist[index]);
				}
				else
				{
					strcpy(str,"lsp"); //set to garbage so invalid error is printed
				}

			}
		}



		//if !no excute the command at no in history, so replace appropriately
		if(str[0]=='!' && strlen(str)>1)
		{
			if(str[1]>='0' && str[1]<='9')
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
			execEcho(str);
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
