/*
  xboxhighParser Library Header File.
*/


#include <dirent.h>
#include <iostream>
#include <string> 
#include <stdio.h>

using namespace std;

#ifndef XPARSER_H 
#define XPARSER_H 0xffffffff 
#endif  /* #ifndef GLOBALFUNC_H */   

struct FInfo{
		FILE *headerFile;
		FILE *bodyFile;
		FILE *xmlFile;
		FILE *offsetFile;
		FILE *offsetModFile;
};

void writeToXML(FInfo _file, string xmlStr[128]);
string parseTitle(char *_bodyBuff);					//Parse Title from Body Files
void parseToXml(FInfo _file);
