#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<unistd.h>
#include<iostream>

#include<vector>
#include<string>
#include<fcntl.h>

using namespace std;

int main()
{
	char str[1000],temp[1000];
	scanf("%[^\n]",str);
	getchar();
	strcpy(temp,str);

	char *token;
	token=strtok(str," ");
	if(token)
	{
		printf("%s\n",token);
		token=strtok(NULL," ");
	}
	printf("%s***\n",token);
	printf("%s\n",temp);
	
	//handling files
	int fd;
	char buf[1000];
	scanf("%[^\n]",buf);
	int n=sizeof(buf);
	buf[n]='\n';
	n++;
	fd=creat("History.txt",0644);
	fd=open("History.txt",O_RDWR);
	write(fd,&buf,n);
	close(fd);

	printf("*********************\n\n");
	vector<string> v;
	v.push_back("hello idit\n");
	v.push_back("wake up kid\n");

	int i;
	for(i=0;i<v.size();i++)
	{
		cout<<v[i];
	}

	
	v[1]="changes  made\n";
	for(i=0;i<v.size();i++)
	{
		cout<<v[i];
	}

	return 0;
}

