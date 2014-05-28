#include "urlListManage.h"
#include "globalFunc.h"

int seedDistributing(string _basePath[], int _childID[], int _childNum)
{
	string renameFilePath[10]; 
	FILE *oriURLList;
	FILE *distributedURLList[_childNum];
	int URLCount = 0;
	char Line[10 * 1024];
	char *find = 0;
	int childIDCount = 0;
	
	oriURLList = fopen(_basePath[0].c_str(), "r");
	if(oriURLList == NULL)
	{
		cout << "Original URL List File Read Error !" << endl;
	  return -1;
	}

	for(int i = 0; i < 10; i++)
	{
		renameFilePath[i] = _basePath[i] + itoa(_childID[i]);
		
		distributedURLList[i] = fopen(renameFilePath[i].c_str(), "w+");
		if(oriURLList == NULL)
		{
			cout << "Distributing URL List File Read Error !" << endl;
		  return -1;
		}
		
		//cout << renameFilePath[i] << endl;
	}
	
	while(fgets(Line, 10 * 1024 - 1, oriURLList))
	{
		//char TmpStr[10 * 1024];
		if ((find = strrchr(Line, '\n')))
		{				
			*find = '\0';
			
			if(URLCount < 20)
			{
				switch(childIDCount = (URLCount % 10))
				{
				case 0:
					fputs(Line, distributedURLList[childIDCount]);
					fputs("\n", distributedURLList[childIDCount]);
					break;
				case 1:
					fputs(Line, distributedURLList[childIDCount]);
					fputs("\n", distributedURLList[childIDCount]);
					break;
				case 2:
					fputs(Line, distributedURLList[childIDCount]);
					fputs("\n", distributedURLList[childIDCount]);
					break;
				case 3:
					fputs(Line, distributedURLList[childIDCount]);
					fputs("\n", distributedURLList[childIDCount]);
					break;
				case 4:
					fputs(Line, distributedURLList[childIDCount]);
					fputs("\n", distributedURLList[childIDCount]);
					break;
				case 5:
					fputs(Line, distributedURLList[childIDCount]);
					fputs("\n", distributedURLList[childIDCount]);
					break;
				case 6:
					fputs(Line, distributedURLList[childIDCount]);
					fputs("\n", distributedURLList[childIDCount]);
					break;
				case 7:
					fputs(Line, distributedURLList[childIDCount]);
					fputs("\n", distributedURLList[childIDCount]);
					break;
				case 8:
					fputs(Line, distributedURLList[childIDCount]);
					fputs("\n", distributedURLList[childIDCount]);
					break;
				case 9:
					fputs(Line, distributedURLList[childIDCount]);
					fputs("\n", distributedURLList[childIDCount]);
					break;	
				}
				/*
				if((URLCount % 10) == 0 && URLCount != 0)
				{
					childIDCount++;
				}
				fputs(Line, distributedURLList[childIDCount]);
				fputs("\n", distributedURLList[childIDCount]);
				*/
				URLCount++;
			}
			
		}
	}
	fclose(oriURLList);
	
	for(int i = 0; i < 10; i++)
		fclose(distributedURLList[i]);
		
	return 1;
}

int DitributionOfSeeds(char *_basePath, int _newChildID)
{
	char childFilePath[128];
	char mvFileCmd[256];
	
	bzero(&childFilePath, sizeof(childFilePath));
	bzero(&mvFileCmd, sizeof(mvFileCmd));
	
	strcpy(childFilePath, _basePath);
	strcat(childFilePath, itoa(_newChildID).c_str());
	
	strcpy(mvFileCmd, "mv ");
	strcat(mvFileCmd, _basePath);
	strcat(mvFileCmd, " ");
	strcat(mvFileCmd, childFilePath);
	
	//cout << mvFileCmd << endl;
	system(mvFileCmd);
	
	return 1;
}

int parseExLinks(FInfo *_file)
{
	int firstShiftIndex;
	int pivot = 0;
	int index = 0;
	
	char *contentBuff;	
	int resul = 0;
	
  fseek(_file->ExLinks, 0, SEEK_END);  
  int size = ftell(_file->ExLinks);
  rewind(_file->ExLinks);
  
	contentBuff = (char*)malloc(sizeof(char) * size);
	if(contentBuff == NULL) {fputs ("Memory error (Content BUFF)\n", stderr); exit (2);}
						
  resul = fread(contentBuff, 1, size, _file->ExLinks);
  if(resul != size) {fputs ("Reading error (Content BUFF)\n", stderr);exit(2);}
  	
  while(pivot < resul)
  {
  	char eachLink[1024];
  	
  	if(contentBuff[pivot] == '<')
  	{
  		if(contentBuff[pivot + 3] == '>')
  		{
  			firstShiftIndex = 4;
  			while(contentBuff[pivot + firstShiftIndex] != '<' && index < 1024)
  			{
  				memcpy(&eachLink[index], &contentBuff[pivot + firstShiftIndex], 1);
  				index++;
  				firstShiftIndex++;
  			}  			
  			memcpy(&eachLink[index], "\n", 1);
  			index++;
  			fwrite(eachLink, 1, index, _file->UniLinks);
  			index = 0;
  			pivot += firstShiftIndex;
  		}
  	}
  	pivot++;
  }
	
	return 1;
}

int seedAssignment(FInfo *_file)
{
	int URLBuffSize = 1024;
	char seedURL[URLBuffSize + 1];
	
	rewind(_file->UniLinks);
	while(fgets(seedURL, URLBuffSize, _file->UniLinks))
	{
		
	}
	
	return 1;
}

int distributeSeed(FInfo *_file)
{
	//Parse links to a file//
	parseExLinks(_file);
	
	//Filter URLs to another file//
	//system("../xboxhigh_bloomFilter/BeginFilter ");
	
	//Assign Seeds to seperating file//
	seedAssignment(_file);
	
	return 1;
}

