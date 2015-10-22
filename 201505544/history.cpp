
#include "headers.h"

//history
#define SIZE 100
char hist[SIZE][1002]; //local history bffer
int curIndex=0; //curIndex for the histBuffer
int startIndex=0; //startIndex for the histBuffer
int capacity=SIZE; //capacity of histBuffer
int curSize=0; //size of histBuffer at any time; 0 to start with

//add every command entered in shell to histBuffer and write taht to history.txt
void addToHist(char str[])
{
	char temp[1000];
	sprintf(temp,"%s",str);
	//printf("###%s",temp); 
	

	//if history is filled to full, increment startIndex as well to make room as well as ignore the oldest command
	if(curSize==capacity)
	{
		startIndex=(startIndex+1)%capacity;
		strcpy(hist[curIndex],temp);
		curIndex=(curIndex+1)%capacity;
	}

	else if(curSize<capacity) //if not full
	{
		strcpy(hist[curIndex],temp); //jst copy to curentIndex nd increment it
		curIndex=(curIndex+1)%capacity;
		curSize++;
	}
}



//restore history ie read history.txt to local hist buffer
void restoreHistory()
{
	int c;
	char temp[1000];
	FILE *f1 = fopen("history.txt","r");

	printf("***********restoring**********\n");
	if(f1!=NULL)
	{
		int i=0;
		while((c=fgetc(f1))!=EOF)
		{
			if(c=='\n')
			{
				printf("%s**\n",temp);
				addToHist(temp);
				i=0;
				memset(&temp[0],0,sizeof(temp));
				continue;
			}
			temp[i]=c;
			i++;
		}
		fclose(f1);
	}
	else
	{
		printf("no file\n");
		return;
	}
}



//print the local buffer to history file
void printToFile()
{
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

}

//print the whole history
void printAll()
{
	int i;
	int index=startIndex;;
	for(i=0;i<curSize;i++)
	{
		printf("%s\n",hist[index]);
		index=(index+1)%capacity;
	}
}


//print the last n lines
void printCount(int n)
{
	if(n>=capacity) //if outof bounds print whole history
		printAll();
	else if(n<=0)
	{
		printf("error: invalid arguement\n");
	}
	else
	{
		int index=(startIndex+curSize-n)%capacity;
		while(index<0)
			index+=capacity;
		int i=0;
		while(i<n)
		{
			printf("%s\n",hist[index]);
			i++;
			index=(index+1)%capacity;
		}
	}
}

//exeute history command
void execHistory(char str[])
{
	char *token;
	token=strtok(str," ");
	token=strtok(NULL," ");
	if(token==NULL)
	{
		printAll();
	}
	else
		printCount(atoi(token));
}


