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

vector<Cmdnodeptr> parseStr(char str[], char *dltr);

//auxillaryFuncs.cpp
void execCommand(char str[]);
void execCd(char str[]);
void execPwd();

