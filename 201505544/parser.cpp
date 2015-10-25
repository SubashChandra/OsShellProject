//parsers the given input string into a vector of structures based on the delimitor
#include "headers.h"


vector<Cmdnodeptr> parseStr(char str[], char dltr[])
{
	vector<Cmdnodeptr>v;
	Cmdnodeptr temp;

	char *token;
	token=strtok(str,dltr);

	while(token)
	{
		temp=(Cmdnodeptr)malloc(sizeof(Cmdnode));
		strcpy(temp->str,token);
		v.push_back(temp);
		token=strtok(NULL,dltr);
	}
	
	int i;
	//for(i=0;i<v.size();i++)
	//	printf("%s\n",v[i]->str);
	return v;
}

