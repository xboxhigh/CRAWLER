/*
  XML Parser Library.
*/
#ifndef XMLPARSER_H 
#define XMLPARSER_H 

#include <dirent.h>
#include <iostream>
#include <string>

#include "globalFunc.h"

using namespace std;


#define MIN_XML_HEADER_BUFF_SZIE 16*1024							//16KB
#define MIN_XML_BODY_BUFF_SZIE 16*1024*1024							//16MB
#define MIN_LINE_LENGTH 128							//128KB
#define MIN_LINE_NUM 128							//128 lines



char *getUrlLists(char *_sourceXml);

#endif  /* #ifndef GLOBALFUNC_H */   
