/*
	Global Function Library Header File
*/

#ifndef GLOBALFUNC_H 
#define GLOBALFUNC_H 

#include <iostream>
#include <string> 
#include <stdio.h>
#include <dirent.h>		
#include <signal.h>
#include <sys/wait.h>

using namespace std;

#define MIN_BUFFER_SZIE 16*1024							//16KB
#define MAX_LINE_LENGTH 128									//128KB Maximum each line length

struct FInfo{
		FILE *Header;
		FILE *Content;
		FILE *OriOffset;
		FILE *MetaInfo;
		FILE *ExLinks;
		FILE *UniLinks;
		FILE *UnCmpLinks;		
		FILE *DistributedSeeds;
		
		FILE *checkFile;
};

struct Offset{
	int BegCOffset;
	int EndCOffset;
	int BegOffset;
	int EndOffset;
};

struct IndexNums{
	int firstShiftIndex;
	int secondShiftIndex;
	int tarIndex;
	int pivot;
	int elements;
};

struct TagStr
{
	char fourChr[5];
	char fiveChr[6];
	char sixChr[7];
	char sevenChr[8];
	
	string begOffset;
	string endOffset;
};

string itoa(int _num);

char *getFileContent(FILE *_file);
char *getFileContent(FILE *_file, long _begOffset, long _endOffset);
long getFileSize(FILE *_file);
int getOffsetFromOriFile(FILE *_oriOffsetFile, string _dest[]);
void checkChildLife(int _sig);
void reapchild(int _sig);
void itoa(int x, char* str);

#endif  /* #ifndef GLOBALFUNC_H */ 
