#include "headers.h"

<<<<<<< HEAD:main.cpp
#define SIZE 100
//global variables
char promptString[1000];
char hist[SIZE][1002]; //local history bffer
int curIndex=0; //curIndex for the histBuffer
int startIndex=0; //startIndex for the histBuffer
int capacity=SIZE; //capacity of histBuffer
int curSize=0; //size of histBuffer at any time; 0 to start with
=======
#define HISTSIZE 100
//global variables
char promptString[1000];
vector<string> hist[HISTSIZE]; //local history bffer
int curIndex=0; //curIndex for the histBuffer
int startIndex=0;
int count=0;

>>>>>>> cbd37fc57710fbbd404bc5cdbddf6a7d39b86002:201505544/main.cpp

void addToHist(char str[])
{
	char temp[1000];
	sprintf(temp,"%s",str);
	//printf("###%s",temp); 
<<<<<<< HEAD:main.cpp
	

	//if history is filled to full, increment startIndex as well to make room as well as ignore the oldest command
	if(curSize+1==capacity)
	{
		startIndex=(startIndex+1)%capacity;
		strcpy(hist[curIndex],temp);
		curIndex=(curIndex+1)%capacity;
	}

	else if(curSize+1<capacity) //if not full
	{
		strcpy(hist[curIndex],temp); //jst copy to curentIndex nd increment it
		curIndex=(curIndex+1)%capacity;
		curSize++;
	}

	///now that copy is done, open the file and write the whole histBuffer to file
	FILE *f1 = fopen("history.txt","w");
	int i=0,j=startIndex;
	while(i<curSize)
	{
		fprintf(f1,"%s\n",hist[j]);
		j=(j+1)%capacity;
		i++;
	}
	fclose(f1);
=======

	strcpy(hist[curIndex],temp);

	if(count==HISTSIZE) //if the history is already full
	{
		//we should insert current commands but start ignoring first commands
		startIndex++;
	}

	//for the first 100 insertions 
	if(count<HISTSIZE)
		count++;

	curIndex++;
	//check if the curIndex jas reached end
	if(curIndex==100) 
		curIndex=0; //reset it


	FILE *fp=fopen("History.txt","w");
	if(startIndex

	fclose(fp);
>>>>>>> cbd37fc57710fbbd404bc5cdbddf6a7d39b86002:201505544/main.cpp
}


	


int main()
{
	//restore history if there is any
//	restoreHistory();
	
	char str[10000],temp[10000];	
	//do a infinite loop of command prompt
	getcwd(promptString,1000);
	printf("%s### ",promptString);
	while(1)
	{
		scanf("%[^\n]",str);
		getchar();
		//everytime add current command to localbuffer 
		//nd add to the history file
		addToHist(str);
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
			printf("history command in progress\n");

				
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
		printf("%s### ",promptString);

	}
	return 0;
}
