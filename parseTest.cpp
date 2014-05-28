/*
  Program IV : Provide Parsing Function
*/

#include <dirent.h>
#include <iostream>
#include <string>


#include "globalFunc.h"

using namespace std;

struct IndexNums
{
	int firstShiftIndex;
	int secondShiftIndex;
	int tarIndex;
	int pivot;
	int elements;
};

string replaceCharacter(char _char)
{
	string repStr;
	
	if(_char == '&')
		repStr = "$amp;";
	else if(_char == '\"')
		repStr = "&quot;";
	else if(_char == '\'')
		repStr = "&apos;";
	else if(_char == '<')
		repStr = "&lt;";
	else if(_char == '>')
		repStr = "&gt;";
	else
		repStr = _char;
	//cout << "(\'" << repStr << "\')"<< endl;
	return repStr;

}

int checkTypePerLink(IndexNums &_Index, char *_src, string &_tar)
{
	if(_src[_Index.pivot + _Index.firstShiftIndex + _Index.secondShiftIndex] == '\"')
	{
		_Index.secondShiftIndex += 1;
		while(_src[_Index.pivot + _Index.firstShiftIndex + _Index.secondShiftIndex] != '\"')
		{
			_tar += replaceCharacter(_src[_Index.pivot + _Index.firstShiftIndex + _Index.secondShiftIndex]);								
			_Index.secondShiftIndex++;
		}
	}
	else if(_src[_Index.pivot + _Index.firstShiftIndex + _Index.secondShiftIndex] == '\'')
	{
		_Index.secondShiftIndex += 1;
		while(_src[_Index.pivot + _Index.firstShiftIndex + _Index.secondShiftIndex] != '\'')
		{
			_tar += replaceCharacter(_src[_Index.pivot + _Index.firstShiftIndex + _Index.secondShiftIndex]);								
			_Index.secondShiftIndex++;
		}
	}
	else
	{
		_Index.secondShiftIndex += 1;
		while(_src[_Index.pivot + _Index.firstShiftIndex + _Index.secondShiftIndex] != '>')
		{
			_tar += replaceCharacter(_src[_Index.pivot + _Index.firstShiftIndex + _Index.secondShiftIndex]);								
			_Index.secondShiftIndex++;
		}
	}
	//cout << _tar.length() << " ) " << _tar << endl;
	return 1;
}

int combinationTags(FInfo _file, string _src, char _tagType)
{
	
	switch(_tagType)
	{
	case 'i':					//<img tag//
		fputs("<im>", _file.ExLinks);
		fwrite(_src.c_str(), 1, _src.length(),_file.ExLinks);
		fputs("</im>", _file.ExLinks);
		break;
	case 'b':					//<base tag//
		fputs("<ba>", _file.ExLinks);
		fwrite(_src.c_str(), 1, _src.length(),_file.ExLinks);
		fputs("</ba>", _file.ExLinks);
		break;
	case 'a':					//<a href tag//
		fputs("<ah>", _file.ExLinks);
		fwrite(_src.c_str(), 1, _src.length(),_file.ExLinks);
		fputs("</ah>", _file.ExLinks);
		break;
	case 'l':					//<link tag//
		fputs("<li>", _file.ExLinks);
		fwrite(_src.c_str(), 1, _src.length(),_file.ExLinks);
		fputs("</li>", _file.ExLinks);
		break;
	case 'f':					//form tag//
		fputs("<fo>", _file.ExLinks);
		fwrite(_src.c_str(), 1, _src.length(),_file.ExLinks);
		fputs("</fo>", _file.ExLinks);
		break;
	case 'r':					//<iframe tag//
		fputs("<if>", _file.ExLinks);
		fwrite(_src.c_str(), 1, _src.length(),_file.ExLinks);
		fputs("</if>", _file.ExLinks);
		break;
	}	
	return 1;	
}

int combinationWithBaseURL(string _baseURL, string &_tar)
{
	string tmpStr;
	tmpStr = "";
	
	if((_tar[0] == '#' && _tar.length() > 1) || (_tar[0] == '/' && _tar.length() > 1))
	{
		tmpStr = _baseURL + _tar.substr(1, _tar.length());
		_tar = tmpStr;
	}
	else if((_tar[0] == '#' && _tar.length() == 1) || (_tar[0] == '/' && _tar.length() == 1))
		_tar = _baseURL;
	else if(_tar[0] != 'h' && _tar.length() > 1)
	{
		tmpStr = _baseURL + _tar;
		_tar = tmpStr;
	}
	else
		return 1;
	
	return 1;
}

int linksExtracting(FInfo _file, char *_contentBuff, string _baseURL)
{
	int buffSize = strlen(_contentBuff);
	bool baseURLTriger = false;
	
	TagStr CmpStr;
	IndexNums Index;
	string baseURL;
	string tmpURLBuff;
	
	Index.firstShiftIndex = 0;
	Index.secondShiftIndex = 0;
	Index.tarIndex = 0;
	Index.pivot = 0;
	Index.elements = 0;
	
	//Default base URL//
	baseURL = "";
	
	//The The highest priority//
	while(Index.pivot < buffSize)
	{
		Index.firstShiftIndex = 0;
		Index.secondShiftIndex = 0;
			
		if(_contentBuff[Index.pivot] == '<')
		{
			//Begin spliting <base href=> tags//
			if(tolower(_contentBuff[Index.pivot + 1]) == 'b')
			{
				
				CmpStr.fourChr[0] = tolower(_contentBuff[Index.pivot + 1]);
				CmpStr.fourChr[1] = tolower(_contentBuff[Index.pivot + 2]);
				CmpStr.fourChr[2] = tolower(_contentBuff[Index.pivot + 3]);
				CmpStr.fourChr[3] = tolower(_contentBuff[Index.pivot + 4]);
				CmpStr.fourChr[4] = '\0';
				
				if(strcmp(CmpStr.fourChr, "base") == 0)
				{
					Index.pivot += 5;
					
					while(_contentBuff[Index.pivot + Index.firstShiftIndex] != '>')
					{
						CmpStr.fiveChr[0] = tolower(_contentBuff[Index.pivot + Index.firstShiftIndex + 1]);
						CmpStr.fiveChr[1] = tolower(_contentBuff[Index.pivot + Index.firstShiftIndex + 2]);
						CmpStr.fiveChr[2] = tolower(_contentBuff[Index.pivot + Index.firstShiftIndex + 3]);
						CmpStr.fiveChr[3] = tolower(_contentBuff[Index.pivot + Index.firstShiftIndex + 4]);
						CmpStr.fiveChr[4] = tolower(_contentBuff[Index.pivot + Index.firstShiftIndex + 5]);
						CmpStr.fiveChr[5] = '\0';
						
						if(strcmp(CmpStr.fiveChr, "href=") == 0)
						{
							Index.secondShiftIndex += 6;
																			
							checkTypePerLink(Index, _contentBuff, tmpURLBuff);
							baseURLTriger = true;
						}
						Index.firstShiftIndex++;
					}
				}
				Index.pivot = Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex;
			}
		}
		Index.pivot++;
	}
	
	if(!baseURLTriger)
		baseURL = _baseURL;
		
	//Check orther tags//
	Index.pivot = 0;
	while(Index.pivot < buffSize)
	{
		Index.firstShiftIndex = 0;
		Index.secondShiftIndex = 0;
		tmpURLBuff = "";
		baseURLTriger = false;
			
		if(_contentBuff[Index.pivot] == '<')
		{		
			/*
			//Begin spliting <img src> tags & <iframe src>tags//
			if(tolower(_contentBuff[Index.pivot + 1]) == 'i')
			{
				if(tolower(_contentBuff[Index.pivot + 2]) == 'm')
				{					
					CmpStr.fourChr[0] = _contentBuff[Index.pivot];
					CmpStr.fourChr[1] = tolower(_contentBuff[Index.pivot + 1]);
					CmpStr.fourChr[2] = tolower(_contentBuff[Index.pivot + 2]);
					CmpStr.fourChr[3] = tolower(_contentBuff[Index.pivot + 3]);
					CmpStr.fourChr[4] = '\0';	
					
					
					if(strcmp(CmpStr.fourChr, "<img") == 0)
					{
						Index.pivot += 4;
						
						while(_contentBuff[Index.pivot + Index.firstShiftIndex] != '>')
						{
							CmpStr.fourChr[0] = tolower(_contentBuff[Index.pivot + 1]);
							CmpStr.fourChr[1] = tolower(_contentBuff[Index.pivot + 2]);
							CmpStr.fourChr[2] = tolower(_contentBuff[Index.pivot + 3]);
							CmpStr.fourChr[3] = tolower(_contentBuff[Index.pivot + 4]);
							CmpStr.fourChr[4] = '\0';
							
							//cout << Index.firstShiftIndex << " ) (" << Index.secondShiftIndex << endl;
							//cout << _contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex] << endl;
								
							if(strcmp(CmpStr.fourChr, "src=") == 0)
							{
								Index.secondShiftIndex += 3;
								checkTypePerLink(Index, _contentBuff, tmpURLBuff);
								combinationWithBaseURL(baseURL, tmpURLBuff);
								combinationTags(_file, tmpURLBuff, 'i');
							}
							Index.firstShiftIndex++;
						}
					}					
				}
				else if(tolower(_contentBuff[Index.pivot + 2]) == 'f')
				{
					CmpStr.sixChr[0] = tolower(_contentBuff[Index.pivot + 1]);
					CmpStr.sixChr[1] = tolower(_contentBuff[Index.pivot + 2]);
					CmpStr.sixChr[2] = tolower(_contentBuff[Index.pivot + 3]);
					CmpStr.sixChr[3] = tolower(_contentBuff[Index.pivot + 4]);
					CmpStr.sixChr[4] = tolower(_contentBuff[Index.pivot + 5]);
					CmpStr.sixChr[5] = tolower(_contentBuff[Index.pivot + 6]);
					CmpStr.sixChr[6] = '\0';
					
					if(strcmp(CmpStr.sixChr, "iframe") == 0)
					{
						Index.pivot += 7;
						
						while(_contentBuff[Index.pivot + Index.firstShiftIndex] != '>')
						{
							CmpStr.fourChr[0] = tolower(_contentBuff[Index.pivot + 1]);
							CmpStr.fourChr[1] = tolower(_contentBuff[Index.pivot + 2]);
							CmpStr.fourChr[2] = tolower(_contentBuff[Index.pivot + 3]);
							CmpStr.fourChr[3] = tolower(_contentBuff[Index.pivot + 4]);
							CmpStr.fourChr[4] = '\0';
							
							if(strcmp(CmpStr.fourChr, "src=") == 0)
							{
								Index.secondShiftIndex += 5;
								
								checkTypePerLink(Index, _contentBuff, tmpURLBuff);
								combinationWithBaseURL(baseURL, tmpURLBuff);
								combinationTags(_file, tmpURLBuff, 'r');
							}
							Index.firstShiftIndex++;
						}
					}
				}
			}
			*/
			
			//Begin spliting <link href=> tags//
			if(tolower(_contentBuff[Index.pivot + 1]) == 'l')
			{
				CmpStr.fourChr[0] = tolower(_contentBuff[Index.pivot + 1]);
				CmpStr.fourChr[1] = tolower(_contentBuff[Index.pivot + 2]);
				CmpStr.fourChr[2] = tolower(_contentBuff[Index.pivot + 3]);
				CmpStr.fourChr[3] = tolower(_contentBuff[Index.pivot + 4]);
				CmpStr.fourChr[4] = '\0';
				
				if(strcmp(CmpStr.fourChr, "link") == 0)
				{
					Index.pivot += 5;
					
					while(_contentBuff[Index.pivot + Index.firstShiftIndex] != '>')
					{
						CmpStr.fiveChr[0] = tolower(_contentBuff[Index.pivot + Index.firstShiftIndex + 1]);
						CmpStr.fiveChr[1] = tolower(_contentBuff[Index.pivot + Index.firstShiftIndex + 2]);
						CmpStr.fiveChr[2] = tolower(_contentBuff[Index.pivot + Index.firstShiftIndex + 3]);
						CmpStr.fiveChr[3] = tolower(_contentBuff[Index.pivot + Index.firstShiftIndex + 4]);
						CmpStr.fiveChr[4] = tolower(_contentBuff[Index.pivot + Index.firstShiftIndex + 5]);
						CmpStr.fiveChr[5] = '\0';
						
						if(strcmp(CmpStr.fiveChr, "href=") == 0)
						{
							Index.secondShiftIndex += 6;
							
							checkTypePerLink(Index, _contentBuff, tmpURLBuff);
							combinationWithBaseURL(baseURL, tmpURLBuff);
							combinationTags(_file, tmpURLBuff, 'l');
						}
						Index.firstShiftIndex++;
					}
				}
			}
			
			//Begin spliting <form action=> tags//
			if(tolower(_contentBuff[Index.pivot + 1]) == 'f')
			{
				CmpStr.fourChr[0] = tolower(_contentBuff[Index.pivot + 1]);
				CmpStr.fourChr[1] = tolower(_contentBuff[Index.pivot + 2]);
				CmpStr.fourChr[2] = tolower(_contentBuff[Index.pivot + 3]);
				CmpStr.fourChr[3] = tolower(_contentBuff[Index.pivot + 4]);
				CmpStr.fourChr[4] = '\0';
				
				if(strcmp(CmpStr.fourChr, "form") == 0)
				{
					Index.pivot += 5;
					
					while(_contentBuff[Index.pivot + Index.firstShiftIndex] != '>')
					{
						CmpStr.sevenChr[0] = tolower(_contentBuff[Index.pivot + Index.firstShiftIndex + 1]);
						CmpStr.sevenChr[1] = tolower(_contentBuff[Index.pivot + Index.firstShiftIndex + 2]);
						CmpStr.sevenChr[2] = tolower(_contentBuff[Index.pivot + Index.firstShiftIndex + 3]);
						CmpStr.sevenChr[3] = tolower(_contentBuff[Index.pivot + Index.firstShiftIndex + 4]);
						CmpStr.sevenChr[4] = tolower(_contentBuff[Index.pivot + Index.firstShiftIndex + 5]);
						CmpStr.sevenChr[5] = tolower(_contentBuff[Index.pivot + Index.firstShiftIndex + 6]);
						CmpStr.sevenChr[6] = tolower(_contentBuff[Index.pivot + Index.firstShiftIndex + 7]);
						CmpStr.sevenChr[7] = '\0';
						
						if(strcmp(CmpStr.fiveChr, "action=") == 0)
						{
							Index.secondShiftIndex += 8;
														
							checkTypePerLink(Index, _contentBuff, tmpURLBuff);
							combinationWithBaseURL(baseURL, tmpURLBuff);
							combinationTags(_file, tmpURLBuff, 'f');							
						}
						Index.firstShiftIndex++;
					}
				}
			}
			
			//Begin spliting <a href=> tags//
			if(tolower(_contentBuff[Index.pivot + 1]) == 'a')
			{
				Index.pivot += 2;
				
				//cout << _contentBuff[Index.pivot + Index.firstShiftIndex + 1] << endl;
				
				while(_contentBuff[Index.pivot + Index.firstShiftIndex] != '>')
				{
					CmpStr.fiveChr[0] = tolower(_contentBuff[Index.pivot + Index.firstShiftIndex + 1]);
					CmpStr.fiveChr[1] = tolower(_contentBuff[Index.pivot + Index.firstShiftIndex + 2]);
					CmpStr.fiveChr[2] = tolower(_contentBuff[Index.pivot + Index.firstShiftIndex + 3]);
					CmpStr.fiveChr[3] = tolower(_contentBuff[Index.pivot + Index.firstShiftIndex + 4]);
					CmpStr.fiveChr[4] = tolower(_contentBuff[Index.pivot + Index.firstShiftIndex + 5]);
					CmpStr.fiveChr[5] = '\0';
										
					if(strcmp(CmpStr.fiveChr, "href=") == 0)
					{
						Index.secondShiftIndex += 6;
						
						checkTypePerLink(Index, _contentBuff, tmpURLBuff);						
						combinationWithBaseURL(baseURL, tmpURLBuff);
						combinationTags(_file, tmpURLBuff, 'a');						
					}
					Index.firstShiftIndex++;					
				}
			}
			
			Index.pivot += tmpURLBuff.length();
		}
		Index.pivot++;
	}
	
	return 1;
}

int XMLParser(FInfo _file, char *_OffsetBuff)
{
	int buffPerRead = 16 * 1024;
	int buffIndex = 0;
	char *contentBuff;
	char *scanKey;
	TagStr _TAG;
	
	contentBuff = (char*)malloc(sizeof(char) * buffPerRead);
	
	while(fgets(contentBuff, buffPerRead - 1, _file.Header))
	{
		contentBuff[buffPerRead] = '\0';
		
		for(int key = 0; key < buffPerRead; key++)
		{
			_TAG.fiveChr[0] = contentBuff[key];
			_TAG.fiveChr[1] = contentBuff[key + 1];
			_TAG.fiveChr[2] = contentBuff[key + 2];
			_TAG.fiveChr[3] = contentBuff[key + 3];
			_TAG.fiveChr[4] = contentBuff[key + 4];
			_TAG.fiveChr[5] = '\0';
			
			if(strcmp(_TAG.fiveChr, "<beg>") == 0)
			{
				key += 5;
								
				while(true)
				{
					if(contentBuff[key] != '<')
					{
						_TAG.begOffset += contentBuff[key];
						key++;
					}
					else
					{
						_TAG.begOffset += "\n";
						break;
					}
				}
				memcpy(&_OffsetBuff[buffIndex], _TAG.begOffset.c_str(), _TAG.begOffset.length());
				buffIndex += _TAG.begOffset.length();
				//cout << "Beg : " << _TAG.begOffset;
			}
			
			if(strcmp(_TAG.fiveChr, "<end>") == 0)
			{
				key += 5;
								
				while(true)
				{
					if(contentBuff[key] != '<')
					{
						_TAG.endOffset += contentBuff[key];
						key++;
					}
					else
					{
						_TAG.endOffset += "\n";
						break;
					}
				}
				memcpy(&_OffsetBuff[buffIndex], _TAG.endOffset.c_str(), _TAG.endOffset.length());
				buffIndex += _TAG.endOffset.length();
				//cout << "End : "<< _TAG.endOffset;
			}
			
			_TAG.begOffset = "";
			_TAG.endOffset = "";
		}
	}
	
	free(contentBuff);
	
	return 1;
}

int baseURLEx(FILE *_file, string &_tar)
{
	int buffPerRead = 128 + 1;
	int buffIndex = 0;
	char *contentBuff;
	char *scanKey;
	TagStr _TAG;
	
	contentBuff = (char*)malloc(sizeof(char) * buffPerRead);
	
	while(fgets(contentBuff, buffPerRead - 1, _file))
	{
		contentBuff[buffPerRead] = '\0';
		
		for(int key = 0; key < buffPerRead; key++)
		{
			_TAG.fiveChr[0] = contentBuff[key];
			_TAG.fiveChr[1] = contentBuff[key + 1];
			_TAG.fiveChr[2] = contentBuff[key + 2];
			_TAG.fiveChr[3] = contentBuff[key + 3];
			_TAG.fiveChr[4] = contentBuff[key + 4];
			_TAG.fiveChr[5] = '\0';
			
			if(strcmp(_TAG.fiveChr, "<URL>") == 0)
			{
				key += 5;
												
				while(true)
				{
					if(contentBuff[key] != '<')
					{
						_tar += contentBuff[key];
						key++;
					}
					else
					{
						//_TAG.begOffset += "\n";						
						break;
					}
				}
				free(contentBuff);
				return 1;
			}
		}
	}
	return 1;
}

int readContent(FInfo _file, char *_offsetBuff)
{
	int begOffset = 0;
	int endOffset = 0;
	int size = 0;
	int key = 0;
	int resul = 0;
	
	char *contentBuff;
	char *pch;
	string baseURL;
	
	string tmpTitleTag = "<LINK>";
	string tmpEndTag = "</LINK>";
	
	contentBuff = (char*)malloc(sizeof(char) * (16 * 1024 * 1024));
	if(contentBuff == NULL) {fputs ("Memory error (Content BUFF)\n", stderr); exit (2);}
		
  pch = strtok(_offsetBuff, "\n");
  
  while(pch != NULL)
  {
		if(key % 2 != 0)
		{
			endOffset = atoi(pch);
			
			if(key > 0)				
			{	
    		size = endOffset - begOffset;
    		
    		cout << "=================================" << endl;
    		cout << "OFFSET : " << begOffset << "\t" << endOffset << "\t" << size << endl;
    		
    		fseek(_file.Content, begOffset, SEEK_SET);
    		resul = fread(contentBuff, 1, size, _file.Content);

    		cout << resul << "\t" << size << "\t[" << ftell(_file.Content) << "]" << endl;
    		cout << "=================================\n" << endl;
    		
    		if(resul != size) {fputs ("Reading error (Content BUFF)\n", stderr); exit(3);}
    		
    		baseURL = "";
				baseURLEx(_file.Header, baseURL);
				
				fwrite(tmpTitleTag.c_str(), 1, tmpTitleTag.length(), _file.ExLinks);
    		linksExtracting(_file, contentBuff, baseURL);
    		fputs(tmpEndTag.c_str(), _file.ExLinks);
				
    		free(contentBuff);
    		contentBuff = (char*)malloc(sizeof(char) * (16 * 1024 * 1024));
				if(contentBuff == NULL) {fputs ("Memory error (Content BUFF)\n", stderr); exit (2);}
    	}
		}
		else
		{
			begOffset = atoi(pch);
		}
		
    pch = strtok(NULL, "\n");
    key++;
  }
  
	return 1;
}


int extractHeaderData(FInfo _file)
{
	char *OffsetBuff;
	int buffSize = 256 * 1024 * 1024;			//256MB
	OffsetBuff = (char*)malloc(sizeof(char) * buffSize);
	
	string xmlTileStr = "<?xml version='1.0' encoding='utf-8'?><EXLINKS>";
	string xmlEndTag = "</EXLINKS>\0";
		
	XMLParser(_file, OffsetBuff);
	rewind(_file.Header);
	
	fwrite(xmlTileStr.c_str(), 1, xmlTileStr.length(), _file.ExLinks);	
	readContent(_file, OffsetBuff);
	fputs(xmlEndTag.c_str(), _file.ExLinks);
	
	free(OffsetBuff);
	return 1;
}

int main(int argc, char **argv)
{
	FInfo FILEVAR;
	string tmpBuf[60];
	bool signal = true;
	string procID = "";	
	
	if(argc < 2 || argc > 2)
  {
    printf("%s <Child ID> \n", argv[0]);
    exit(1);
  }
  
  //procID = "18808";
  procID = argv[1];  
  
 
	if(procID != "")
	{
		 /*Initial File Name*/
		string contentFileName = "/data2/xboxhigh/_gatheringFiles/bFile/Content." + procID;
		string headerFileName = "/data2/xboxhigh/_gatheringFiles/hFile/Header." + procID;
		string extractLinksFileName = "/data2/xboxhigh/_gatheringFiles/xFile/extractLinks." + procID;
	
		/*Open Files*/
		FILEVAR.Content = fopen(contentFileName.c_str(), "r");
			if (FILEVAR.Content == NULL) cout << "No Such Path [" << contentFileName << "]\n";
		FILEVAR.Header = fopen(headerFileName.c_str(), "r");
			if (FILEVAR.Header == NULL) cout << "No Such Path [" << headerFileName << "]\n";
		FILEVAR.ExLinks = fopen(extractLinksFileName.c_str(), "w+");
			if (FILEVAR.ExLinks == NULL) cout << "No Such Path" << extractLinksFileName << "]\n";
		
		extractHeaderData(FILEVAR);
		
		fclose(FILEVAR.Content);
	  fclose(FILEVAR.Header);
	  fclose(FILEVAR.ExLinks);
	}
	else
	{
		cout << "Please give me the child ID !" << endl;
		exit(1);
	}
	
	
  
  
	return 0;
}
