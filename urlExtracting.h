#ifndef URLEXTRACTING_H 
#define URLEXTRACTING_H

#include <dirent.h>
#include <iostream>
#include <string>

#include "globalFunc.h"

using namespace std;

int extractHeaderData(FInfo *_file);
//int combinationWithBaseURL(string _baseURL, string &_tar);
string replaceCharacter(char _char);

//int combinationTags(FInfo *_file, string _src, char _tagType);

int XMLParser(FInfo *_file, char *_OffsetBuff);

int baseURLEx(FILE *_file, char *_tar);
int LinksExtracting(FILE *_file, char *_contentBuff, char *_baseURL, int _buffSize);
int CombinationTags(FInfo *_file, char *_src, char _tagType);
int CombinationWithBaseURL(char *_baseURL, char *_tar);
int CheckBaseLinks(char *_contentBuff, char *_baseURL);
int checkTypePerLink(IndexNums *_Index, char *_src, char *_tar);
int FindBaseURL(char *_src, char *_tar, int _curURL);

#endif  /* #ifndef URLEXTRACTING_H */     
