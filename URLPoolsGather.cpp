/*
	Parse XML component
*/

#include "xmlParser.h"
#include "globalFunc.h"

#include <iostream>
#include <dirent.h>

using namespace std;

int main(void)
{
	
	FInfo FILEVAR;
	int fileCount[7] = {0, 0, 0, 0, 0, 0};			//To give each file a single number
	char *urlLists;
	char *tmpBuff;
	int Esize = 0;
	
	/*Initial File Name*/
	string extractLinksFileName = "/data1/xboxhigh/_gatheringFiles/xFile/extractLinks.out." + itoa(fileCount[0]) + ".xml";
	string seedsFileName = "/data1/xboxhigh/_gatheringFiles/pFile/urlPools.out." + itoa(fileCount[1]) + ".xml";
	
	/*Open Files*/
	FILEVAR.extractLinks = fopen(extractLinksFileName.c_str(), "r");
		if (FILEVAR.extractLinks == NULL) cout << "No Such Path" << endl;
	FILEVAR.seedsFile = fopen(seedsFileName.c_str(), "w+");
		if (FILEVAR.seedsFile == NULL) cout << "No Such Path" << endl;
			
	
	Esize = getFileSize(FILEVAR.extractLinks);
		
	tmpBuff = (char*)malloc(sizeof(char) * Esize);
	
	cout << Esize << endl;
	tmpBuff = getFileContent(FILEVAR.extractLinks);
	
	urlLists = getUrlLists(tmpBuff);
	
	
	fputs(urlLists, FILEVAR.seedsFile);		//Generating OffsetFiles
	
	/*Close Files*/
  fclose(FILEVAR.extractLinks);
  fclose(FILEVAR.seedsFile);
  
  
	return 0;
}
