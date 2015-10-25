//header file to include all libs nd file declarations

#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cstring>


#include<unistd.h>
#include<vector>
#include<string>
#include<fcntl.h>
#include<sys/wait.h>

//handling signals
#include<signal.h>

using namespace std;

struct cmdnode
{
	char str[1000];
};

typedef struct cmdnode Cmdnode;
typedef Cmdnode *Cmdnodeptr;


//pileFuncs.cpp
int hasPipe(char str[]);
int pipeCount(char str[]);
void executePipe(vector<Cmdnodeptr> v, int n);


//parser.cpp

vector<Cmdnodeptr> parseStr(char str[], char dltr[]);

//auxillaryFuncs.cpp
void execCommand(char str[]);
void execCd(char str[]);
void execPwd();
void execExport(char str[]);
void removeQuotes(char val[]);

//history.cpp

//vars
#define SIZE 100
extern char hist[SIZE][1002]; //local history bffer
extern int curIndex; //curIndex for the histBuffer
extern int startIndex; //startIndex for the histBuffer
extern int capacity; //capacity of histBuffer
extern int curSize; //size of histBuffer at any time; 0 to start with

//functions
void addToHist(char str[]);
void restoreHistory();
void printToFile();
void printAll();
void printCount(int n);
void execHistory(char str[]);


//echo.cpp
void execEcho(char str[]);
void runEcho(char str[]);
void replaceEnv(char str[],char temp[]);
