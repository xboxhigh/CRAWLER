/*
  xboxhighParser Library Header File.
*/
#ifndef XPARSER_H 
#define XPARSER_H 0xffffffff 

#include <dirent.h>
#include <iostream>
#include <string>

#include "globalFunc.h"

using namespace std;

#define MIN_XML_HEADER_BUFF_SZIE 16*1024							//16KB
#define MIN_XML_BODY_BUFF_SZIE 16*1024*1024							//16MB
#define MIN_LINE_LENGTH 128							//128KB
#define MIN_LINE_NUM 128							//128 lines

struct IndexNums
{
	int firstShiftIndex;
	int secondShiftIndex;
	int srcIndex;
	int tarIndex;
	int elements;
};


void addXmlTag(string _xmlStrBuff[], int _xmlStrBuffSize, string _splitStr[]);
int splitStrByDelimiters(string _xmlStrBuff[], char *_splitStr, char splitOpt, int _buffSize);
char *parseHeaderFile(FInfo _file);
char *parseBodyFile(FInfo _file);
void addTags(string _target[], string _source[], int _srcSize);
string replaceCharacter(char _char);
int splitContentToString(char *_target, char *_source, char _splitOpt);
int splitStrByDeli(char *_targ, char *_src, string _del);
IndexNums checkStrTagType(char *_tar, char *_src, IndexNums _index);

#endif  /* #ifndef GLOBALFUNC_H */   
