/*
  Program IV : Provide Parsing Function
*/

#include "urlExtracting.h"

/*Split header and add xml tag*/
void addXmlTag(string _xmlStrBuff[], int _xmlStrBuffSize, string _splitStr[])
{
	int xmlStrBuffIndex = 0;
		
	for(int i = 0; i < _xmlStrBuffSize; i++)
	{
		if(_splitStr[i].compare("HTTP/1.1") == 0)
		{
			string statusCode = _splitStr[i + 1].substr(0, 1);
			
			switch(atoi(statusCode.c_str()))
			{
				case 1:
					//cout << statusCode << "	" << _splitStr[i + 1] << endl;
					_xmlStrBuff[xmlStrBuffIndex] = "<sCode>" + _splitStr[i + 1] + "</sCode>";												//Record the status code
					xmlStrBuffIndex++;
					break;
				case 2:
					//cout << statusCode << "	" << _splitStr[i + 1] << endl;
					_xmlStrBuff[xmlStrBuffIndex] = "<sCode>" + _splitStr[i + 1] + "</sCode>";												//Record the status code
					xmlStrBuffIndex++;
					break;
				case 3:
					//cout << statusCode << "	" << _splitStr[i + 1] << endl;
					_xmlStrBuff[xmlStrBuffIndex] = "<sCode>" + _splitStr[i + 1] + "</sCode>";												//Record the status code
					xmlStrBuffIndex++;
					_xmlStrBuff[xmlStrBuffIndex] = "<jLink>" + _splitStr[i + 4] + "</jLink>";												//If status code is 3XX, records the jumping link 
					xmlStrBuffIndex++;
					break;
				case 4:
					//cout << statusCode << "	" << _splitStr[i + 1] << endl;
					_xmlStrBuff[xmlStrBuffIndex] = "<sCode>" + _splitStr[i + 1] + "</sCode>";												//Record the status code
					xmlStrBuffIndex++;
					break;
				case 5:
					//cout << statusCode << "	" << _splitStr[i + 1] << endl;
					_xmlStrBuff[xmlStrBuffIndex] = "<sCode>" + _splitStr[i + 1] + "</sCode>";												//Record the status code
					xmlStrBuffIndex++;
					break;
			}
		}
		else if(_splitStr[i].compare("Cache-Control:") == 0)
		{
			_xmlStrBuff[xmlStrBuffIndex] = "<cControl>" + _splitStr[i + 1] + "</cControl>";
			xmlStrBuffIndex++;
		}
		else if(_splitStr[i].compare("Content-Type:") == 0)
		{
			_xmlStrBuff[xmlStrBuffIndex] = "<cType>" + _splitStr[i + 1] + _splitStr[i + 2] + "</cType>";
			xmlStrBuffIndex++;
		}
		else if(_splitStr[i].compare("Connection:") == 0)
		{
			_xmlStrBuff[xmlStrBuffIndex] = "<connection>" + _splitStr[i + 1] + "</connection>";
			xmlStrBuffIndex++;
		}
		else if(_splitStr[i].compare("Date:") == 0)
		{
			_xmlStrBuff[xmlStrBuffIndex] = "<date><week>" + _splitStr[i + 1] + "</week><day>" + _splitStr[i + 2] + "</day><month>" + 
														_splitStr[i + 3] + "</month><year>" + _splitStr[i + 4] + "</year><time>" + 
														_splitStr[i + 5] + "</time><timeZone>" + _splitStr[i + 6] + "</timeZone></date>";
			xmlStrBuffIndex++;
		}
		else if(_splitStr[i].compare("Transfer-Encoding:") == 0)
		{
			_xmlStrBuff[xmlStrBuffIndex] = "<tEncoding>" + _splitStr[i + 1] + "</tEncoding>";
			xmlStrBuffIndex++;
		}
		else if(_splitStr[i].compare("Expires:") == 0)
		{
			_xmlStrBuff[xmlStrBuffIndex] = "<expires><week>" + _splitStr[i + 1] + "</week><day>" + _splitStr[i + 2] + "</day><month>" + 
														_splitStr[i + 3] + "</month><year>" + _splitStr[i + 4] + "</year><time>" + 
														_splitStr[i + 5] + "</time><timeZone>" + _splitStr[i + 6] + "</timeZone></expires>";
			xmlStrBuffIndex++;
		}
		/*
		else if(_splitStr[i].compare("Set-Cookie:") == 0)
		{
			int nextSetCookiePos = 1;

			_xmlStrBuff[xmlStrBuffIndex] = "<sCookie>";
		  
		  while(_splitStr[i + nextSetCookiePos].find(",") != string::npos && _splitStr[i + nextSetCookiePos].find(";") != string::npos )
		  {
		    cout << _splitStr[i + nextSetCookiePos] << "	" << int(_splitStr[i + nextSetCookiePos].find(",")) << "	" << int(_splitStr[i + nextSetCookiePos].find(";")) << endl;

		    nextSetCookiePos++;
			}
			
			_xmlStrBuff[xmlStrBuffIndex] += "</sCookie>";
			
			xmlStrBuffIndex++;
		}
		*/
	}
	
}

/*Add XML tag to body links*/
void addTags(string _target[], string _source[], int _srcSize)
{
	string tmpStr;
	char *catchStr, *buffStr;
	string splitStr[2];
	int splitIndex;
	
	for(int i = 0; i < 2; i++)
		splitStr[i] = "";
	
	for(int srcLen = 0; srcLen < _srcSize; srcLen++)
	{
		splitIndex = 0;
		
		/*Split _source to type and link*/
		catchStr = new char[_source[srcLen].size() + 1];
		strcpy (catchStr, _source[srcLen].c_str());
		
		buffStr = strtok (catchStr, "@");
		while (buffStr != NULL)
	  {
	    splitStr[splitIndex] = buffStr;
	    //cout << buffStr << endl;
	    buffStr = strtok(NULL,"@");
	    splitIndex++;
	  }
		
		
		/*Add diff type tag to according to its split type
			splitStr[0]	:	type
			splitStr[1] : link
		*/
		
		if(splitStr[0].compare("if") == 0)
		{
			_target[srcLen] = "<IFRAME>" + splitStr[1] + "</IFRAME>";
		}
		else if(splitStr[0].compare("ah") == 0)
		{
			_target[srcLen] = "<A>" + splitStr[1] + "</A>";
		}
		else if(splitStr[0].compare("im") == 0)
		{
			_target[srcLen] = "<IMG>" + splitStr[1] + "</IMG>";
		}
		else if(splitStr[0].compare("li") == 0)
		{
			_target[srcLen] = "<LINK>" + splitStr[1] + "</LINK>";
		}
		else if(splitStr[0].compare("fo") == 0)
		{
			_target[srcLen] = "<FORM>" + splitStr[1] + "</FORM>";
		}
		else if(splitStr[0].compare("ba") == 0)
		{
			_target[srcLen] = "<BASE>" + splitStr[1] + "</BASE>";
		}
		else if(splitStr[0].compare("sc") == 0)
		{
			_target[srcLen] = "<SCRIPT>" + splitStr[1] + "</SCRIPT>";
		}
	}
}

IndexNums checkStrTagType(char *_tar, char *_src, IndexNums _index)
{
	string cache;
	
	if(_src[_index.srcIndex + _index.firstShiftIndex + _index.secondShiftIndex] == '\"')
	{
		_index.secondShiftIndex += 1;
		while(_src[_index.srcIndex + _index.firstShiftIndex + _index.secondShiftIndex] != '\"')
		{
			cache = _src[_index.srcIndex + _index.firstShiftIndex + _index.secondShiftIndex];
			
			memcpy(&_tar[_index.tarIndex], cache.c_str(), 1);
			_index.tarIndex += 1;	
			_index.secondShiftIndex++;
			
		}		
	
		memcpy(&_tar[_index.tarIndex], "\n", 1);
		_index.tarIndex += 1;
		_index.elements++;		
	}	
	else if(_src[_index.srcIndex] == '\'')
	{
		_index.secondShiftIndex += 1;
		while(_src[_index.srcIndex + _index.firstShiftIndex + _index.secondShiftIndex] != '\'')
		{
			cache = _src[_index.srcIndex + _index.firstShiftIndex + _index.secondShiftIndex];
			
			memcpy(&_tar[_index.tarIndex], cache.c_str(), 1);
			_index.tarIndex += 1;							
			_index.secondShiftIndex++;
		}
		
		memcpy(&_tar[_index.tarIndex], "\n", 1);
		_index.tarIndex += 1;
		_index.elements++;
	}	
	else
	{
		
	}
	return _index;
}

/*Split Pages Contents
	
		Split Option:
			O	:	Offset Files
			H : Header Files
			B : Body Files
			P : URL Pools
*/
int splitContentToString(char *_target, char *_source, char _splitOpt)
{
	char *firstCmpStr;
	char *secondCmpStr;
	
	IndexNums index;
	
	index.tarIndex = 0;
	index.srcIndex = 0;
	index.elements = 0;
	
	int firstCmpStrIndex;
	int secondCmpStrIndex;	
		
	switch(_splitOpt)
	{
	case 'H':		
		return splitStrByDeli(_target, _source, "\r\n");
		break;
	case 'B':
		//Put source contents tolower//
		for(index.srcIndex = 0; index.srcIndex < strlen(_source); index.srcIndex++)
			_source[index.srcIndex] = tolower(_source[index.srcIndex]);
		

		for(index.srcIndex = 0; index.srcIndex < strlen(_source); index.srcIndex++)
		{
			//Initial varialbs Begin//
			firstCmpStr = (char*)malloc(sizeof(char) * 8);
			secondCmpStr = (char*)malloc(sizeof(char) * 8);

			index.firstShiftIndex = 0;
			index.secondShiftIndex = 0;
			firstCmpStrIndex = 0;
			secondCmpStrIndex = 0;
			//Initial varialbs End//
			
			if(_source[index.srcIndex] == '<')
			{			
				//Begin spliting <a href=> tags//
				if(_source[index.srcIndex + 1] == 'a')					
				{
					for(int firstCmpStrIndex = 0; firstCmpStrIndex < 2; firstCmpStrIndex++)
						firstCmpStr[firstCmpStrIndex] = _source[index.srcIndex + firstCmpStrIndex];
						
					if(strcmp(firstCmpStr, "<a") == 0)
					{
						index.firstShiftIndex += 2;
						
						while(_source[index.srcIndex + index.firstShiftIndex] != '>')
						{	
							for(secondCmpStrIndex = 0; secondCmpStrIndex < 5; secondCmpStrIndex++)
								secondCmpStr[secondCmpStrIndex] = _source[index.srcIndex + index.firstShiftIndex + secondCmpStrIndex];
								
							if(strcmp(secondCmpStr, "href=") == 0)
							{					
								index.secondShiftIndex += 5;
								
								index = checkStrTagType(_target, _source, index);
								
							}
							index.firstShiftIndex++;
						}
						index.srcIndex = index.srcIndex + index.firstShiftIndex + index.secondShiftIndex;
					}
				}
				
				//Begin spliting <img src> tags & <iframe src>tags//
				else if(_source[index.srcIndex + 1] == 'i')
				{						
					if(_source[index.srcIndex + 2] == 'm')
					{
						for(int firstCmpStrIndex = 0; firstCmpStrIndex < 4; firstCmpStrIndex++)
							firstCmpStr[firstCmpStrIndex] = _source[index.srcIndex + firstCmpStrIndex];
						
						if(strcmp(firstCmpStr, "<img") == 0)
						{								
							index.firstShiftIndex += 4;
							
							while(_source[index.srcIndex + index.firstShiftIndex] != '>')
							{	
								for(int secondCmpStrIndex = 0; secondCmpStrIndex < 4; secondCmpStrIndex++)
									secondCmpStr[secondCmpStrIndex] = _source[index.srcIndex + index.firstShiftIndex + secondCmpStrIndex];
				
								if(strcmp(secondCmpStr, "src=") == 0)
								{					
									index.secondShiftIndex += 4;
									
									index = checkStrTagType(_target, _source, index);
									
								}
								index.firstShiftIndex++;
							}
							index.srcIndex = index.srcIndex + index.firstShiftIndex + index.secondShiftIndex;
						}
					}
					else if(_source[index.srcIndex + 2] == 'f')
					{
						
						for(int firstCmpStrIndex = 0; firstCmpStrIndex < 6; firstCmpStrIndex++)
							firstCmpStr[firstCmpStrIndex] = _source[index.srcIndex + firstCmpStrIndex];
							
						if(strcmp(firstCmpStr, "<iframe") == 0)
						{
							index.firstShiftIndex += 6;
							
							
							while(_source[index.srcIndex + index.firstShiftIndex] != '>')
							{	
								for(int secondCmpStrIndex = 0; secondCmpStrIndex < 4; secondCmpStrIndex++)
									secondCmpStr[secondCmpStrIndex] = _source[index.srcIndex + index.firstShiftIndex + secondCmpStrIndex];
				
								if(strcmp(secondCmpStr, "src=") == 0)
								{					
									index.secondShiftIndex += 4;
									
									index = checkStrTagType(_target, _source, index);
								}
							}
							index.firstShiftIndex++;
						}
						index.srcIndex = index.srcIndex + index.firstShiftIndex + index.secondShiftIndex;
					}
				}
				
				//Begin spliting <link href=> tags//
				else if(_source[index.srcIndex + 1] == 'l')	
				{
					for(int firstCmpStrIndex = 0; firstCmpStrIndex < 5; firstCmpStrIndex++)
						firstCmpStr[firstCmpStrIndex] = _source[index.srcIndex + firstCmpStrIndex];
					
					if(strcmp(firstCmpStr, "<link") == 0)
					{
						index.firstShiftIndex += 5;
						
						while(_source[index.srcIndex + index.firstShiftIndex] != '>')
						{	
							for(int secondCmpStrIndex = 0; secondCmpStrIndex < 5; secondCmpStrIndex++)
								secondCmpStr[secondCmpStrIndex] = _source[index.srcIndex + index.firstShiftIndex + secondCmpStrIndex];
							
							if(strcmp(secondCmpStr, "href=") == 0)
							{			
								index.secondShiftIndex += 5;
								
								index = checkStrTagType(_target, _source, index);
							}
							index.firstShiftIndex++;
						}
						index.srcIndex = index.srcIndex + index.firstShiftIndex + index.secondShiftIndex;
					}
				}
				
				//Begin spliting <base href=> tags//
				else if(_source[index.srcIndex + 1] == 'b')	
				{
					for(int firstCmpStrIndex = 0; firstCmpStrIndex < 5; firstCmpStrIndex++)
						firstCmpStr[firstCmpStrIndex] = _source[index.srcIndex + firstCmpStrIndex];
					
					if(strcmp(firstCmpStr, "<base") == 0)
					{
						index.firstShiftIndex += 5;
						
						while(_source[index.srcIndex + index.firstShiftIndex] != '>')
						{	
							for(int secondCmpStrIndex = 0; secondCmpStrIndex < 5; secondCmpStrIndex++)
								secondCmpStr[secondCmpStrIndex] = _source[index.srcIndex + index.firstShiftIndex + secondCmpStrIndex];
							
							if(strcmp(secondCmpStr, "href=") == 0)
							{			
								index.secondShiftIndex += 5;
								
								index = checkStrTagType(_target, _source, index);
								
							}
							index.firstShiftIndex++;
						}
						index.srcIndex = index.srcIndex + index.firstShiftIndex + index.secondShiftIndex;
					}
				}
				
				//Begin spliting <form action=> tags//
				else if(_source[index.srcIndex + 1] == 'f')	
				{
					for(int firstCmpStrIndex = 0; firstCmpStrIndex < 5; firstCmpStrIndex++)
						firstCmpStr[firstCmpStrIndex] = _source[index.srcIndex + firstCmpStrIndex];
					
					if(strcmp(firstCmpStr, "<form") == 0)
					{
						index.firstShiftIndex += 5;
						
						while(_source[index.srcIndex + index.firstShiftIndex] != '>')
						{	
							for(int secondCmpStrIndex = 0; secondCmpStrIndex < 7; secondCmpStrIndex++)
								secondCmpStr[secondCmpStrIndex] = _source[index.srcIndex + index.firstShiftIndex + secondCmpStrIndex];
								
							if(strcmp(secondCmpStr, "action=") == 0)
							{			
								index.secondShiftIndex += 7;
								
								index = checkStrTagType(_target, _source, index);
								
							}
							index.firstShiftIndex++;
						}
						index.srcIndex = index.srcIndex + index.firstShiftIndex + index.secondShiftIndex;
					}
				}
			}
		
		}
		return index.elements;
		break;
	case 'O':
		return splitStrByDeli(_target, _source, "\t");
		break;
	case 'P':
		return splitStrByDeli(_target, _source, "\n");
		break;
	default:
		cout << "No such option type" << endl;
		abort();
		break;
	}
	
}

/*Split string by delimiters*/
int splitStrByDeli(char *_targ, char *_src, string _del)
{	
	char *tmpStrBuff;
	int targetIndex = 0;
	int elementCount = 0;
	
	tmpStrBuff = strtok(_targ, _del.c_str());
		
	while(tmpStrBuff != NULL)
	{
		memcpy(&_targ[targetIndex], tmpStrBuff, strlen(tmpStrBuff));
		targetIndex = targetIndex + strlen(tmpStrBuff);
		memcpy(&_targ[targetIndex], "\n", 1);
		targetIndex = targetIndex + 1;
	  tmpStrBuff = strtok(NULL, _del.c_str());
	  
	  elementCount++;
	}
	
	return elementCount;
}


/*Split String by Delimiters*/
int splitStrByDelimiters(string _xmlStrBuff[], char *_splitStr, char splitOpt, int _offset)
{
	string offsetDelimiters = "\t";	
	string headerDelimiters = " \r\n";
	string bodyDelimiters = "\n";
	
	string tmpStrByLine[_offset];
	
	char *offsetStr;
	char *headerStr;
	char *bodyStr;
	char *poolStr;
	int eleCount = 0;
	

	string tmpStr = "";
	string shiftStr[8];
	
	int shiftNum = 0;					//For first shifting flag of buff
	int secondShiftNum = 0;		//For second shifting flag of buff
	
	switch(splitOpt)
	{
	/*--		Split OffsetFile		--*/
	case 'O':		
		offsetStr = strtok(_splitStr, offsetDelimiters.c_str());
		
		while(offsetStr != NULL)
		{
			_xmlStrBuff[eleCount] = offsetStr;
		  offsetStr = strtok(NULL, offsetDelimiters.c_str());
		  //cout << _xmlStrBuff[eleCount] << endl;
		  eleCount++;
		  
		}
		return eleCount;
		break;
	/*--		Split Header File		--*/
	case 'H':
		headerStr = strtok(_splitStr, headerDelimiters.c_str());
		
		while(headerStr != NULL)
		{
			_xmlStrBuff[eleCount] = headerStr;
		  headerStr = strtok(NULL, headerDelimiters.c_str());
		  //cout << _xmlStrBuff[eleCount] << endl;
		  eleCount++;
		  
		}
				
		return eleCount;
		break;
	/*--		Split Body File		--*/
	case 'B':
		for(int buffIndex = 0; buffIndex < strlen(_splitStr); buffIndex++)
			_splitStr[buffIndex] = tolower(_splitStr[buffIndex]);
		
		
		return eleCount;		
		break;
	case 'P':
		poolStr = strtok(_splitStr, bodyDelimiters.c_str());
		
		while(poolStr != NULL)
		{
			_xmlStrBuff[eleCount] = poolStr;
		  poolStr = strtok(NULL, bodyDelimiters.c_str());
		  //cout << _xmlStrBuff[eleCount] << endl;
		  eleCount++;			
		}
		return eleCount;
		break;
	default:
		cout << "Operation Fail" << endl;
		abort();
	}
	
	return eleCount;
	
}

/*Parse a header file to a malloc memory spcae*/
char *parseHeaderFile(FInfo _file)
{
	char *XML_HEADER_BUFF = (char*)malloc(sizeof(char) * MIN_XML_HEADER_BUFF_SZIE);					//Finshed XML File Buffer
	int xHeaderBuffIndex = 0;
	
	char *tmpOffsetBuff = (char*)malloc(sizeof(char) * MIN_LINE_LENGTH);			//Malloc a 128kb memory 
	string getLines[MIN_LINE_NUM];										//Get Offset File lines 
	string getLineElement[5];							//Get Offset File one line which contains 5 elements
	int lineCount = 0;
	
	char *headerBuff;
	size_t hResult;
	
	
	/*Add offsetFile's data in string array*/
	rewind(_file.oriHBOffset);							//Let offsetFile pointer to 0
	while(fgets(tmpOffsetBuff , 128, _file.oriHBOffset) != NULL)	
	{		
		getLines[lineCount] = tmpOffsetBuff;
		//cout << getLines[lineCount];
		lineCount++;
	}
	
	//cout << lineCount << endl;
	/*Start Parsing*/
	int rowCount = 1;													//Ignore OffsetFile first row
	long offset = 0;
	
	string xmlTileStr = "<?xml version='1.0' encoding='utf-8'?><HEADINFOFILEINFO>";
	
	memcpy(&XML_HEADER_BUFF[xHeaderBuffIndex], xmlTileStr.c_str(), xmlTileStr.size());
	xHeaderBuffIndex = xHeaderBuffIndex + xmlTileStr.size();
	
	while(rowCount < lineCount)
	{
		string tmpTitleTag = "<LINK_" + itoa(rowCount) + ">";
		string tmpEndTag = "</LINK_" + itoa(rowCount) + ">";
		
		memcpy(&XML_HEADER_BUFF[xHeaderBuffIndex], tmpTitleTag.c_str(), tmpTitleTag.size());
		xHeaderBuffIndex = xHeaderBuffIndex + tmpTitleTag.size();
		
		string xmlBuff[MIN_LINE_NUM + 1];						//Catch each page header's data which has been parsed.
		string addXmlBuff[MIN_LINE_NUM + 1];						//Catch each page header's data which has been parsed and add xml.
		int elementCount = 0;
		
		/*Get header and body offset*/				
		splitStrByDelimiters(getLineElement, (char*)getLines[rowCount].c_str(), 'O', offset);
		
		offset = atoi(getLineElement[2].c_str()) - atoi(getLineElement[1].c_str());					//Calculate page's header offset.
				
		//cout << getLineElement[0] << "   " << getLineElement[1] << "   " << getLineElement[2] << "   " << getLineElement[3] <<"   " << getLineElement[4] << endl;
		
		string seedName = "<SEEDNAME>" + getLineElement[0] + "</SEEDNAME>";
		
		memcpy(&XML_HEADER_BUFF[xHeaderBuffIndex], seedName.c_str(), seedName.size());
		xHeaderBuffIndex = xHeaderBuffIndex + seedName.size();
		
		/*Malloc a block memory to store header.*/
	  fseek(_file.headerFile, offset, SEEK_SET);
	  headerBuff = (char*)malloc(sizeof(char) * offset);
		if(headerBuff == NULL) {fputs ("Memory error (headerBuff)\n", stderr); exit (2);}
			
		/*Read header according header offset*/
		fseek(_file.headerFile, atoi(getLineElement[1].c_str()), SEEK_SET);
		hResult = fread(headerBuff, 1, offset, _file.headerFile);
		if(hResult != offset) {fputs ("Reading error (hResult)\n", stderr); exit (3);}
		
		//cout << headerBuff << endl;
		
		/*Get spliter header*/
		elementCount = splitStrByDelimiters(xmlBuff, headerBuff, 'H', offset);			
		
		/*
		for(int i = 0; i < elementCount; i++)
			cout << i << "		" << xmlBuff[i] << endl;
		
		*/
		/*Add xml tag in header*/
		addXmlTag(addXmlBuff, elementCount, xmlBuff);
		
		
		int i = 0;
				
		while(!addXmlBuff[i].empty())
		{
			memcpy(&XML_HEADER_BUFF[xHeaderBuffIndex], addXmlBuff[i].c_str(), addXmlBuff[i].size());
			xHeaderBuffIndex = xHeaderBuffIndex + addXmlBuff[i].size();
			//cout << i << "		" << addXmlBuff[i] << endl;
			//fputs(addXmlBuff[i].c_str(), _file.pageInfo);		//Generating OffsetFiles
			i++;
		}
					
		memcpy(&XML_HEADER_BUFF[xHeaderBuffIndex], tmpEndTag.c_str(), tmpEndTag.size());
		xHeaderBuffIndex = xHeaderBuffIndex + tmpEndTag.size();
		
		free(headerBuff);
		rowCount++;
	}
	
	string endTag = "</HEADINFOFILEINFO>";
	memcpy(&XML_HEADER_BUFF[xHeaderBuffIndex], endTag.c_str(), endTag.size());
	
	fputs(XML_HEADER_BUFF, _file.pageInfo);		//Generating OffsetFiles
	//cout << XML_HEADER_BUFF << endl;
	
	return XML_HEADER_BUFF;
}


char *parseBodyFile(FInfo _file)
{
	char *XML_BODY_BUFF = (char*)malloc(sizeof(char) * MIN_XML_BODY_BUFF_SZIE);
	int xBodyBuffIndex = 0;
	
	BUFF buff;
	
	char *tmpOffsetBuff = (char*)malloc(sizeof(char) * MIN_LINE_LENGTH);			//Malloc a 128kb memory 
	string getLines[MIN_LINE_NUM];										//Get Offset File lines 
	string getLineElement[5];							//Get Offset File one line which contains 5 elements
	int lineCount = 0;

	size_t bResult;	
	
	/*Add offsetFile's data in string array*/
	rewind(_file.oriHBOffset);							//Let offsetFile pointer to 0
	while(fgets(tmpOffsetBuff, 128, _file.oriHBOffset) != NULL)	
	{		
		getLines[lineCount] = tmpOffsetBuff;
		//cout << getLines[lineCount];
		lineCount++;
	}
		
	/*Start Parsing*/
	int rowCount = 1;								//Ignore OffsetFile first row
	long offset = 0;
	
	//string xmlTileStr = "<?xml version='1.0' encoding='utf-8'?><LINKSFILEINFO>";
	
	//memcpy(&XML_BODY_BUFF[xBodyBuffIndex], xmlTileStr.c_str(), xmlTileStr.size());
	//xBodyBuffIndex = xBodyBuffIndex + xmlTileStr.size();
	
	
	while(rowCount < 4)
	{
		
		//string tmpTitleTag = "<LINK_" + itoa(rowCount) + ">";
		//string tmpEndTag = "</LINK_" + itoa(rowCount) + ">";
		
		//memcpy(&XML_BODY_BUFF[xBodyBuffIndex], tmpTitleTag.c_str(), tmpTitleTag.size());
		//xBodyBuffIndex = xBodyBuffIndex + tmpTitleTag.size();

		/*Get body and body offset*/				
		splitStrByDelimiters(getLineElement, (char*)getLines[rowCount].c_str(), 'O', offset);
		
		offset = atoi(getLineElement[4].c_str()) - atoi(getLineElement[3].c_str());					//Calculate page's body offset.
		
		//cout << getLineElement[0] << "   " << getLineElement[1] << "   " << getLineElement[2] << "   " << getLineElement[3] <<"   " << getLineElement[4];
		

		string xmlBuff[offset];						//Catch each page body's data which has been parsed.
		
		
		
		int elementCount = 0;
		
		/*Malloc a block memory to store body.*/
	  fseek(_file.bodyFile, offset, SEEK_SET);
	  buff.src = (char*)malloc(sizeof(char) * offset);
		if(buff.src == NULL) {fputs ("Memory error (bodyBuff)\n", stderr); exit (2);}
			
		/*Read body according header offset*/
		fseek(_file.bodyFile, atoi(getLineElement[3].c_str()), SEEK_SET);
		bResult = fread(buff.src, 1, offset, _file.bodyFile);
		if(bResult != offset) {fputs ("Reading error (bResult)\n", stderr); exit (3);}
		
		
		cout << "===========[" << getLineElement[0] << "]=============" << endl;
		
		/*Get spliter body*/
		//elementCount = splitStrByDelimiters(xmlBuff, bodyBuff, 'B', offset);
		//elementCount = splitContentToString(reciveBuff, bodyBuff, 'B');
		
		//cout << reciveBuff;
		//fputs(reciveBuff, _file.extractLinks);
		//string linksWithTag[elementCount + 1];

		/*
		for(int k = 0; k < elementCount; k++)
			cout << k << xmlBuff[k] << endl;
		*/
		
		
		//addTags(linksWithTag, xmlBuff, elementCount);
		/*
		for(int k = 0; k < elementCount; k++)
			cout << linksWithTag[k] << endl;
		*/
		
		int i = 0;
		/*
		while(!linksWithTag[i].empty())
		{
			memcpy(&XML_BODY_BUFF[xBodyBuffIndex], linksWithTag[i].c_str(), linksWithTag[i].size());
			xBodyBuffIndex = xBodyBuffIndex + linksWithTag[i].size();
			//cout << i << "		" << linksWithTag[i] << endl;
			//fputs(addXmlBuff[i].c_str(), _file.pageInfo);		//Generating OffsetFiles
			i++;
			
		}
		memcpy(&XML_BODY_BUFF[xBodyBuffIndex], tmpEndTag.c_str(), tmpEndTag.size());
		xBodyBuffIndex = xBodyBuffIndex + tmpEndTag.size();
		
		cout << xBodyBuffIndex << endl;
		*/
		free(buff.src);
		rowCount++;		
		
	}
	
	//string endTag = "</LINKSFILEINFO>";
	//memcpy(&XML_BODY_BUFF[xBodyBuffIndex], endTag.c_str(), endTag.size());
	//xBodyBuffIndex = xBodyBuffIndex + endTag.size();
	
	//fputs(XML_BODY_BUFF, _file.extractLinks);		//Generating OffsetFiles
	//cout << XML_BODY_BUFF << endl;
	return XML_BODY_BUFF;
}


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