/*
	URL List manage Function Library Header File
*/

#ifndef URLLISTMANAGE_H 
#define URLLISTMANAGE_H 

#include <iostream>
#include <string> 
#include <stdio.h>
#include <dirent.h>		

#include "globalFunc.h"

using namespace std;

int seedDistributing(string _basePath[], int _childID[], int _childNum);
int parseExLinks(FInfo *_file);
int seedAssignment(FInfo *_file);
int distributeSeed(FInfo *_file);
int DitributionOfSeeds(char *_basePath, int _newChildID);

#endif  /* #ifndef URLLISTMANAGE_H */ 
