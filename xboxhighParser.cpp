/*
  Program IV : Provide Parsing Function
  
*/

#include "xboxhighParser.h"

using namespace std;

void writeToXML(FInfo _file, string xmlStr[128])
{

	for(int i = 0; i < 128; i++)
	{
		fwrite(xmlStr[i].c_str(), 1, xmlStr[i].length(), _file.xmlFile);		
	}
}

/*Parse Title from Body File*/
string parseTitle(char *_bodyBuff)
{
	int i = 0;
	string tmpStr;
	bool op = true;
	
	while(op != false)
	{
		if(_bodyBuff[i] == '<')
		{
			if(_bodyBuff[i + 1] == 't' ||  _bodyBuff[i + 1] == 'T')
			{
				if(_bodyBuff[i + 2] == 'i' ||  _bodyBuff[i + 2] == 'I')
				{
					if(_bodyBuff[i + 3] == 't' ||  _bodyBuff[i + 3] == 'T')
					{
						if(_bodyBuff[i + 4] == 'l' ||  _bodyBuff[i + 4] == 'L')
						{
							if(_bodyBuff[i + 5] == 'e' ||  _bodyBuff[i + 5] == 'E')
							{
								if(_bodyBuff[i + 6] == '>')
								{
									int j = 7;
									while(_bodyBuff[i + j] != '<')
									{
										if(_bodyBuff[i + j] != '\r' && _bodyBuff[i + j] != '\n' && _bodyBuff[i + j] != '\t' && _bodyBuff[i + j] != ' ')
										{
											tmpStr = tmpStr + _bodyBuff[i + j];											
										}j++;
									}
									op = false;
								}
							}
						}
					}
				}
			}
		}
		i++;
	}
	
	return tmpStr;
}

/*
	Parse to a XML File by using libxml :
	1.Read file in Memory
	2.Extract some infomation to XML
	3.Write to a xml file
*/
void parseToXml(FInfo _file)
{
	char *headerBuff;
	char *bodyBuff;
	size_t hResult;
	size_t bResult;
	long hfSize;
	long bfSize;
	
	int uRow = 0;

	
	int i = 0;
	char *tmpBuff = (char*)malloc(sizeof(char) * 128);
	string urlList[128];
	int e = 0;
	
	int j = 0;
	char *pch;
	char *pchb;
	
	string tmpStr[5];
	string parseHeaderStr[128];
	string parseBodyStr;
	string xmlOutputStr[128];

	fseek (_file.headerFile, 0, SEEK_END);
	fseek (_file.bodyFile, 0, SEEK_END);
	hfSize = ftell(_file.headerFile);
	bfSize = ftell(_file.bodyFile);

	rewind(_file.offsetFile);
	
	while(fgets(tmpBuff , 128, _file.offsetFile) != NULL)	
	{		
		urlList[i] = tmpBuff;		
		i++;
	}
		
	while(uRow < i)
	{
		j = 0;	
		e = 0;
		
		for(int o = 0; o < 128; o++)
			xmlOutputStr[o] = "";
		
		if(uRow == 0)
		{
			xmlOutputStr[e] = "<?xml version='1.0' encoding='UTF-8'?>";
			xmlOutputStr[e + 1] = "<Jam>";
			e += 2;
		}
	
		
		pch = strtok((char*)urlList[uRow].c_str(), "\t\n");
		
	  while(pch != NULL)
	  {
	  	tmpStr[j] = pch;
	    pch = strtok(NULL, "\t\n");
	    j++;
	  }
	  
	    
	  cout << tmpStr[0] << "   " << tmpStr[1] << "   " << tmpStr[2] << "   " << tmpStr[3] <<"   " << tmpStr[4] << endl;
		
		headerBuff = (char*)malloc(sizeof(char) * hfSize);
		if(headerBuff == NULL) {fputs ("Memory error (headerBuff)\n", stderr); exit (2);}
		bodyBuff = (char*)malloc(sizeof(char) * bfSize);
		if(bodyBuff == NULL) {fputs ("Memory error (bodyBuff)\n", stderr); exit (2);}
				
		fseek(_file.headerFile, atoi(tmpStr[1].c_str()), SEEK_SET);
		fseek(_file.bodyFile, atoi(tmpStr[3].c_str()), SEEK_SET);
		
		cout << atoi(tmpStr[2].c_str()) << " " << ftell(_file.headerFile) << endl;
		cout << atoi(tmpStr[4].c_str()) << " " << ftell(_file.bodyFile) << endl;
		
		hResult = fread(headerBuff, 1, atoi(tmpStr[2].c_str()) - atoi(tmpStr[1].c_str()), _file.headerFile);
		if(hResult != atoi(tmpStr[2].c_str()) - atoi(tmpStr[1].c_str())) {fputs ("Reading error (hResult)\n", stderr); exit (3);}
		bResult = fread(bodyBuff, 1, atoi(tmpStr[4].c_str()) - atoi(tmpStr[3].c_str()), _file.bodyFile);
		if(bResult != atoi(tmpStr[4].c_str()) - atoi(tmpStr[3].c_str())) {fputs ("Reading error (hResult)\n", stderr); exit (3);}
		
		/*
		cout << "***********************************************************" << endl;
		cout << headerBuff;
		cout << "***********************************************************" << endl;
		cout << bodyBuff;
		cout << "***********************************************************" << endl;
		*/
		
		pch = strtok(headerBuff, " \r\n");
	  while(pch != NULL)
	  {  	
	  	parseHeaderStr[j] = pch;
	  	//cout << endl << parseHeaderStr[j] << endl << endl;
	    pch = strtok(NULL, " \r\n");
	    
	    j++;
	  }
	  
	  //parseBodyStr = parseTitle(bodyBuff);
	  
	  //cout << "OutPut == " << parseBodyStr << endl ;
	  
	  //xmlOutputStr[e] = "<PAGE>";
	  
	  xmlOutputStr[e] = "<Page>";
	  xmlOutputStr[e + 1] = "<url>" + tmpStr[0] + "</url>";
	  xmlOutputStr[e + 2] = "<title>" + parseBodyStr + "</title>";
	  xmlOutputStr[e + 3] = "<offset><headerstart>" + tmpStr[1] + "</headerstart><headerend>" + tmpStr[2] + "</headerend><bodystart>" 
	  											+ tmpStr[3] + "</bodystart><bodyend>" + tmpStr[4] + "</bodyend></offset>";
	  
	  e += 4;
	  
		for(int k=0; k<20; k++)
		{
			if(parseHeaderStr[k].compare("Content-Type:") == 0)
			{
				xmlOutputStr[e] = "<contenttype>" + parseHeaderStr[k + 1] + parseHeaderStr[k + 2] + "</contenttype>";
				e++;
			}
			else if(parseHeaderStr[k].compare("Date:") == 0)
			{
				xmlOutputStr[e] = "<date>" + parseHeaderStr[k + 1] + parseHeaderStr[k + 2] + parseHeaderStr[k + 3] + "</date>";
				e++;
			}
			else if(parseHeaderStr[k].compare("HTTP/1.1") == 0)
			{
				xmlOutputStr[e] = "<statuscode>" + parseHeaderStr[k + 1] + "</statuscode>";
				e++;
			}
	
		}
		//xmlOutputStr[e] = "</PAGE>";
		xmlOutputStr[e] = "</Page>";
		
		if(uRow == (i - 1))
		{
			e++;
			xmlOutputStr[e] = "</Jam>";
			cout << "     " << xmlOutputStr[e + 1] << endl;
		}
		cout << "++++++++++++++END+++++++++++++++++++++++++++" << endl;
		writeToXML(_file, xmlOutputStr);
			
		uRow++;
	}
	
	
}

