/*
  Program V : Provide common function for using
  
  	string itoa(int _num);
*/

#include "globalFunc.h"

//Convert Int to String//
string itoa(int _num)
{
	char strBuf[128];
	
	sprintf(strBuf, "%d", _num);
	
	return strBuf;
}

void itoa(int x,char* str)
{
        int quo=1,mod=1,i=0,j=0;
        char buffer[32]={0};
        if(0==str)
        {
                return ;
        }
        for(i=0; 0 != quo; ++i)
        {
                mod = x%10;
                quo = x/10;
                x/=10;
                buffer[i]=mod+48;
        }
        for(--i;i>=0;--i,++j)
        {
                str[j] = buffer[i];
        }
        str[j]=0;
}

char *getFileContent(FILE *_file)
{
	long size = 0;	
	int rdRes = 0;
	char *fileContentBuff;
	size = getFileSize(_file);
	//char fileContentBuff[size];
	
	/*Malloc a block memory to store content.*/
	//fileContentBuff = (char*)malloc(sizeof(char) * size);
	//if(fileContentBuff == NULL) {fputs ("Memory error\n", stderr); exit (2);}
		
	/*Read file size according to its reading size.*/
	rewind(_file);
	rdRes = fread(fileContentBuff, 1, size, _file);
	if(rdRes != size) {fputs ("Reading error\n", stderr); exit (3);}
		
	return fileContentBuff;		
}

char *getFileContent(FILE *_file, long _begOffset, long _endOffset)
{
	long size = 0;
	int rdRes = 0;
	char *fileContentBuff;
	size = _endOffset - _begOffset;
	//char fileContentBuff[size];
	
	/*Malloc a block memory to store header.*/	
  fileContentBuff = (char*)malloc(sizeof(char) * size);  
	if(fileContentBuff == NULL) {fputs ("Memory error\n", stderr); exit (2);}
		
	/*Read header according header offset*/
	fseek(_file, _begOffset, SEEK_SET);
	rdRes = fread(fileContentBuff, 1, size, _file);
	if(rdRes != size) {fputs ("Reading error\n", stderr); exit (3);}
		
	return fileContentBuff;
}

long getFileSize(FILE *_file)
{
	long size = 0;
	/*Get File Size*/
	fseek(_file, 0, SEEK_END);
	size = ftell(_file);
	rewind(_file);
	
	return size;
}

int getOffsetFromOriFile(FILE *_oriOffsetFile, string _dest[])
{
	char *tmpOffsetBuff = (char*)malloc(sizeof(char) * MAX_LINE_LENGTH);			//Malloc a 128kb memory 
	int lineCount = 0;
	
	/*Get header & body content offsets*/
	rewind(_oriOffsetFile);							//Let offsetFile pointer to the file begin
	while(fgets(tmpOffsetBuff , 128, _oriOffsetFile) != NULL)	
	{		
		_dest[lineCount] = tmpOffsetBuff;
		free(tmpOffsetBuff);
		tmpOffsetBuff = (char*)malloc(sizeof(char) * MAX_LINE_LENGTH);			//Malloc a 128kb memory 
		lineCount++;
	}
	
	return lineCount;
}

void checkChildLife(int _sig)
{
	/*
	if(_sig == SIGUSR1)
		cout << "Self : ["<< _sig << "]"<< endl;
	*/
	
	/*NOTHING*/; 
}

void reapchild(int _sig) 
{ 
  signal(SIGCHLD, reapchild);	// 加上再設定的動作。 
  
  while(wait(NULL) <= 0 )
    /*NOTHING*/; 
}
