#include <stdio.h>
#include <curl.h> 
#include <dirent.h>
#include <string>
#include <iostream>

using namespace std;

struct FILEMY
{
	FILE *Hfile;
	FILE *Bfile;
};

struct MemoryStruct {
  char *memory;
  size_t size;
};

struct HeaderInfo
{
	char *CURLINFO_RedirURL;
	char *CURLINFO_ContentType;
	long CURLINFO_RepCode;
	double CURLINFO_ContentLen;
};

#define MAX_INI_SEED_NUM 10

string itoa(int _num)
{
	char strBuf[128];
	
	sprintf(strBuf, "%d", _num);
	
	return strBuf;
}

//Write HTML data into a file.//
static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{ 
  int written = fwrite(ptr, size, nmemb, (FILE *)stream);
  
  return written;
}

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;
 
  mem->memory = (char*)realloc(mem->memory, mem->size + realsize + 1);
  //mem->memory = (char*)malloc(sizeof(char) * (mem->size + realsize + 1));

  if (mem->memory == NULL) 
  {
    /* out of memory! */ 
    printf("not enough memory (realloc returned NULL)\n");
    exit(EXIT_FAILURE);
  }
 
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;
  
  return realsize;
}


void extractHeaderData(string _src, char *_tar, int &_tarIndex)
{
	string tmpDeli = "\0";
	string deli = " \r\n";
	string strBuff[512];
	
	char *str;
	char catchStr[_src.length() + 1];
	int tarElement = 0;
	
	/*Split _source to type and link*/
	strcpy(catchStr, _src.c_str());

	
	str = strtok(catchStr, deli.c_str());
	
	while(str != NULL)
	{
		strBuff[tarElement] = str;
		str = strtok(NULL, deli.c_str());
		tarElement++;
	}
	
	//Combine Tags//
	int i = 0;
	
	if(strBuff[i].compare("Cache-Control:") == 0)
	{
		memcpy(&_tar[_tarIndex], "<caCon>", 7);
 		_tarIndex = _tarIndex + 7;
 		memcpy(&_tar[_tarIndex], strBuff[i + 1].c_str(), strBuff[i + 1].length());
 		_tarIndex = _tarIndex + strBuff[i + 1].length();
 		memcpy(&_tar[_tarIndex], strBuff[i + 2].c_str(), strBuff[i + 2].length());
 		_tarIndex = _tarIndex + strBuff[i + 2].length();
 		memcpy(&_tar[_tarIndex], "</caCon>", 8);
 		_tarIndex = _tarIndex + 8;
 		memcpy(&_tar[_tarIndex], tmpDeli.c_str(), tmpDeli.length());
 		_tarIndex = _tarIndex + tmpDeli.length();	
 		/*
		_tar[_tarIndex] = "<cControl>" + strBuff[i + 1] + "</cControl>";
		_tarIndex++;
		*/
	}
	if(strBuff[i].compare("Connection:") == 0)
	{
		memcpy(&_tar[_tarIndex], "<conNe>", 7);
 		_tarIndex = _tarIndex + 7;
 		memcpy(&_tar[_tarIndex], strBuff[i + 1].c_str(), strBuff[i + 1].length());
 		_tarIndex = _tarIndex + strBuff[i + 1].length();
 		memcpy(&_tar[_tarIndex], "</conNe>", 8);
 		_tarIndex = _tarIndex + 8;
 		memcpy(&_tar[_tarIndex], tmpDeli.c_str(), tmpDeli.length());
 		_tarIndex = _tarIndex + tmpDeli.length();	
 		/*
		_tar[_tarIndex] = "<connection>" + strBuff[i + 1] + "</connection>";
		_tarIndex++;
		*/
	}
	if(strBuff[i].compare("Date:") == 0)
	{		
		memcpy(&_tar[_tarIndex], "<date><week>", 12);
 		_tarIndex = _tarIndex + 12;
 		memcpy(&_tar[_tarIndex], strBuff[i + 1].c_str(), strBuff[i + 1].length());
 		_tarIndex = _tarIndex + strBuff[i + 1].length();
 		memcpy(&_tar[_tarIndex], "</week><day>", 12);
 		_tarIndex = _tarIndex + 12;
 		memcpy(&_tar[_tarIndex], strBuff[i + 2].c_str(), strBuff[i + 2].length());
 		_tarIndex = _tarIndex + strBuff[i + 2].length();
 		memcpy(&_tar[_tarIndex], "</day><month>", 13);
 		_tarIndex = _tarIndex + 13;
 		memcpy(&_tar[_tarIndex], strBuff[i + 3].c_str(), strBuff[i + 3].length());
 		_tarIndex = _tarIndex + strBuff[i + 3].length();
 		memcpy(&_tar[_tarIndex], "</month><year>", 14);
 		_tarIndex = _tarIndex + 14;
 		memcpy(&_tar[_tarIndex], strBuff[i + 4].c_str(), strBuff[i + 4].length());
 		_tarIndex = _tarIndex + strBuff[i + 4].length();
 		memcpy(&_tar[_tarIndex], "</year><time>", 13);
 		_tarIndex = _tarIndex + 13;
 		memcpy(&_tar[_tarIndex], strBuff[i + 5].c_str(), strBuff[i + 5].length());
 		_tarIndex = _tarIndex + strBuff[i + 5].length();
 		memcpy(&_tar[_tarIndex], "</time><timeZone>", 17);
 		_tarIndex = _tarIndex + 17;
 		memcpy(&_tar[_tarIndex], strBuff[i + 6].c_str(), strBuff[i + 6].length());
 		_tarIndex = _tarIndex + strBuff[i + 6].length(); 		
 		memcpy(&_tar[_tarIndex], "</timeZone></date>", 18);
 		_tarIndex = _tarIndex + 18;
 		memcpy(&_tar[_tarIndex], tmpDeli.c_str(), tmpDeli.length());
 		_tarIndex = _tarIndex + tmpDeli.length();	
 		
 		/*
		_tar[_tarIndex] = "<date><week>" + strBuff[i + 1] + "</week><day>" + strBuff[i + 2] + "</day><month>" + 
													strBuff[i + 3] + "</month><year>" + strBuff[i + 4] + "</year><time>" + 
													strBuff[i + 5] + "</time><timeZone>" + strBuff[i + 6] + "</timeZone></date>";
		_tarIndex++;
		*/
	}
	if(strBuff[i].compare("Expires:") == 0)
	{
		
		memcpy(&_tar[_tarIndex], "<date><week>", 12);
 		_tarIndex = _tarIndex + 12;
 		memcpy(&_tar[_tarIndex], strBuff[i + 1].c_str(), strBuff[i + 1].length());
 		_tarIndex = _tarIndex + strBuff[i + 1].length();
 		memcpy(&_tar[_tarIndex], "</week><day>", 12);
 		_tarIndex = _tarIndex + 12;
 		memcpy(&_tar[_tarIndex], strBuff[i + 2].c_str(), strBuff[i + 2].length());
 		_tarIndex = _tarIndex + strBuff[i + 2].length();
 		memcpy(&_tar[_tarIndex], "</day><month>", 13);
 		_tarIndex = _tarIndex + 13;
 		memcpy(&_tar[_tarIndex], strBuff[i + 3].c_str(), strBuff[i + 3].length());
 		_tarIndex = _tarIndex + strBuff[i + 3].length();
 		memcpy(&_tar[_tarIndex], "</month><year>", 14);
 		_tarIndex = _tarIndex + 14;
 		memcpy(&_tar[_tarIndex], strBuff[i + 4].c_str(), strBuff[i + 4].length());
 		_tarIndex = _tarIndex + strBuff[i + 4].length();
 		memcpy(&_tar[_tarIndex], "</year><time>", 13);
 		_tarIndex = _tarIndex + 13;
 		memcpy(&_tar[_tarIndex], strBuff[i + 5].c_str(), strBuff[i + 5].length());
 		_tarIndex = _tarIndex + strBuff[i + 5].length();
 		memcpy(&_tar[_tarIndex], "</time><timeZone>", 17);
 		_tarIndex = _tarIndex + 17;
 		memcpy(&_tar[_tarIndex], strBuff[i + 6].c_str(), strBuff[i + 6].length());
 		_tarIndex = _tarIndex + strBuff[i + 6].length(); 		
 		memcpy(&_tar[_tarIndex], "</timeZone></date>", 18);
 		_tarIndex = _tarIndex + 18;
 		memcpy(&_tar[_tarIndex], tmpDeli.c_str(), tmpDeli.length());
 		_tarIndex = _tarIndex + tmpDeli.length();	
 		
 		/*
		_tar[_tarIndex] = "<expires><week>" + strBuff[i + 1] + "</week><day>" + strBuff[i + 2] + "</day><month>" + 
													strBuff[i + 3] + "</month><year>" + strBuff[i + 4] + "</year><time>" + 
													strBuff[i + 5] + "</time><timeZone>" + strBuff[i + 6] + "</timeZone></expires>";
		_tarIndex++;
		*/
	}
	
}

int addTagInHeaderMetaData(char *_src, char *_tar, int &_tarIndex)
{
	string deli = "\r\n";
	string buff[100];
	int eleCount = 0;
	char *headerStr;
	
 	headerStr = strtok(_src, deli.c_str());
	
	while(headerStr != NULL)
	{	
		buff[eleCount] = headerStr;
	  headerStr = strtok(NULL, deli.c_str());	
	  eleCount++;
	}
	
	//cout << "===============Break==============\n" ;
	
	//Add Tags//	 		
	for(int j = 0; j < eleCount; j++)
	{
		extractHeaderData(buff[j], _tar, _tarIndex);
	  //cout << buff[j].length() << ") : "<< buff[j] << endl;
	}

	return 1;
}

void writeHeaderMetaData(CURL *_curl_handle, MemoryStruct _header, FILE *_file)
{
	string tmpDeli = "\0";
	HeaderInfo CurlInfo;
	char *metaHeaderBuff;
	int divisionResl = 0;
	int shiftIndex = 0;
	int code = 0;
	
	string xmlTileStr = "<?xml version='1.0' encoding='utf-8'?><HEADINFOFILEINFO>";
	string tmpTitleTag = "<LINK>";
	string tmpEndTag = "</LINK></HEADINFOFILEINFO>";
	
	metaHeaderBuff = (char*)malloc(sizeof(char) * 1024 * 1024);
	
	memcpy(&metaHeaderBuff[shiftIndex], xmlTileStr.c_str(), xmlTileStr.length());
 		shiftIndex = shiftIndex + xmlTileStr.length();
 	memcpy(&metaHeaderBuff[shiftIndex], tmpDeli.c_str(), tmpDeli.length());
 		shiftIndex = shiftIndex + tmpDeli.length();
 	memcpy(&metaHeaderBuff[shiftIndex], tmpTitleTag.c_str(), tmpTitleTag.length());
 		shiftIndex = shiftIndex + tmpTitleTag.length();
	memcpy(&metaHeaderBuff[shiftIndex], tmpDeli.c_str(), tmpDeli.length());
 		shiftIndex = shiftIndex + tmpDeli.length();	
 	
 	code = curl_easy_getinfo(_curl_handle, CURLINFO_RESPONSE_CODE, &CurlInfo.CURLINFO_RepCode);

	if((CURLE_OK ==	code) && ((CurlInfo.CURLINFO_RepCode / 100) != 4))
 	{
 		memcpy(&metaHeaderBuff[shiftIndex], "<sCode>", 7);
 		shiftIndex = shiftIndex + 7;
 		memcpy(&metaHeaderBuff[shiftIndex], itoa(CurlInfo.CURLINFO_RepCode).c_str(), 3);
 		shiftIndex = shiftIndex + 3;
 		memcpy(&metaHeaderBuff[shiftIndex], "</sCode>", 8);
 		shiftIndex = shiftIndex + 8;
 		memcpy(&metaHeaderBuff[shiftIndex], tmpDeli.c_str(), tmpDeli.length());
 		shiftIndex = shiftIndex + tmpDeli.length();	

	 	if(CURLE_OK ==
			curl_easy_getinfo(_curl_handle, CURLINFO_REDIRECT_URL, &CurlInfo.CURLINFO_RedirURL)
			&& CurlInfo.CURLINFO_RedirURL)
		{
			memcpy(&metaHeaderBuff[shiftIndex], "<reUrl>", 7);
	 		shiftIndex = shiftIndex + 7;
	 		memcpy(&metaHeaderBuff[shiftIndex], CurlInfo.CURLINFO_RedirURL, 
	 						strlen(CurlInfo.CURLINFO_RedirURL));
	 		shiftIndex = shiftIndex + strlen(CurlInfo.CURLINFO_RedirURL);
	 		memcpy(&metaHeaderBuff[shiftIndex], "</reUrl>", 8);
	 		shiftIndex = shiftIndex + 8;
	 		memcpy(&metaHeaderBuff[shiftIndex], tmpDeli.c_str(), tmpDeli.length());
	 		shiftIndex = shiftIndex + tmpDeli.length();	
		}
		if(CURLE_OK ==
			curl_easy_getinfo(_curl_handle, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &CurlInfo.CURLINFO_ContentLen))
		{
			memcpy(&metaHeaderBuff[shiftIndex], "<cLen>", 6);
	 		shiftIndex = shiftIndex + 6;
	 		memcpy(&metaHeaderBuff[shiftIndex], itoa(CurlInfo.CURLINFO_ContentLen).c_str(), 
	 						strlen(itoa(CurlInfo.CURLINFO_ContentLen).c_str()));
	 		shiftIndex = shiftIndex + strlen(itoa(CurlInfo.CURLINFO_ContentLen).c_str());
	 		memcpy(&metaHeaderBuff[shiftIndex], "</cLen>", 7);
	 		shiftIndex = shiftIndex + 7;
	 		memcpy(&metaHeaderBuff[shiftIndex], tmpDeli.c_str(), tmpDeli.length());
	 		shiftIndex = shiftIndex + tmpDeli.length();	
		}
		if(CURLE_OK ==
			curl_easy_getinfo(_curl_handle, CURLINFO_CONTENT_TYPE, &CurlInfo.CURLINFO_ContentType)
			&& CurlInfo.CURLINFO_ContentType)
		{
			cout << CurlInfo.CURLINFO_ContentType << endl;
			memcpy(&metaHeaderBuff[shiftIndex], "<cType>", 7);
	 		shiftIndex = shiftIndex + 7;
	 		memcpy(&metaHeaderBuff[shiftIndex], CurlInfo.CURLINFO_ContentType, 
	 						strlen(CurlInfo.CURLINFO_ContentType));
	 		shiftIndex = shiftIndex + strlen(CurlInfo.CURLINFO_ContentType);
	 		memcpy(&metaHeaderBuff[shiftIndex], "</cType>", 8);
	 		shiftIndex = shiftIndex + 8;
	 		memcpy(&metaHeaderBuff[shiftIndex], tmpDeli.c_str(), tmpDeli.length());
	 		shiftIndex = shiftIndex + tmpDeli.length();	
		}
	}
	else 
		return;
/*
	cout << endl << "========Original====================" << endl;
 	cout << _header.memory << endl;
 	/*
	addTagInHeaderMetaData(_header.memory, metaHeaderBuff, shiftIndex);
	
	memcpy(&metaHeaderBuff[shiftIndex], tmpEndTag.c_str(), tmpEndTag.length());
 		shiftIndex = shiftIndex + tmpEndTag.length();
	memcpy(&metaHeaderBuff[shiftIndex], tmpDeli.c_str(), tmpDeli.length());
 		shiftIndex = shiftIndex + tmpDeli.length();
 		/*
	cout << "=============Combinition===============" << endl;
	cout << "{"<< shiftIndex << "}" << endl;*/
	cout << metaHeaderBuff << endl;
	//fputs(metaHeaderBuff, _file);
 	//divisionResl = CurlInfo.CURLINFO_RepCode / 100;

}

//Gather Web Pages by CURL Lib//
int pageGatheringByCurl(FILEMY _file, char *_url)
{
	CURL *curl_handle;
	CURLcode code;

	struct MemoryStruct Header;
 	struct MemoryStruct Content;
 	
 	char *err;
 	
  Header.memory = (char*)malloc(1);  /* will be grown as needed by the realloc above */ 
  Header.size = 0;    /* no data at this point */ 
  Content.memory = (char*)malloc(1);  /* will be grown as needed by the realloc above */ 
  Content.size = 0;    /* no data at this point */ 
  
  curl_global_init(CURL_GLOBAL_ALL);
	  
  /* init the curl session */ 
  curl_handle = curl_easy_init();
 
  /* set URL to get */ 
  curl_easy_setopt(curl_handle, CURLOPT_URL, _url);
 
  /* no progress meter please */ 
  curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L); 	 	
  
  // send all data to this function  // 
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
	  
	// we want the headers to this file handle //
	curl_easy_setopt(curl_handle,	CURLOPT_WRITEHEADER, (void*)&Header);
		
	//write the body to this file handle//
	curl_easy_setopt(curl_handle,	CURLOPT_WRITEDATA, (void*)&Content);
		
 curl_easy_setopt(curl_handle, CURLOPT_ERRORBUFFER, &err);
	
 	if(CURLE_OK ==curl_easy_perform(curl_handle))
 	{
 		cout << "OK ! " << endl;
 		cout << _url << endl;
 		writeHeaderMetaData(curl_handle, Header, _file.Hfile);
 		
 		
 		fputs(Content.memory, _file.Bfile);
 		fflush(_file.Bfile);
 	}
	else
	{
		cout << "CURL ERROR ! " << endl;
		cout << err << endl;
	}
	
 	//writeHeaderMetaData(curl_handle, Header, _file.Hfile);

  /* cleanup curl stuff */
  curl_easy_cleanup(curl_handle);
	
	return 1;
}

int main(void)
{
	FILEMY _FILEMY;
	//char URLLINK[1024 + 1];
	string URLLINK = "http://www.gamer.com.tw";
	string URLLINK2 = "http://twtraffic.tra.gov.tw/twrail/index.aspx";
 	char *content;
	
	string headerFileName = "HH" ;
  string bodyFileName = "BB";
  
  _FILEMY.Hfile = fopen(headerFileName.c_str(), "w+");
	 	if (_FILEMY.Hfile == NULL) cout << "No Such Path" << endl;
	_FILEMY.Bfile = fopen(bodyFileName.c_str(), "w+");
		if (_FILEMY.Bfile == NULL) cout << "No Such Path" << endl;
	
  if(pageGatheringByCurl(_FILEMY, (char*)URLLINK.c_str()) != 1)
  	cout << "Totally Fail !" << endl;
  else
  {
  	//cout << "Sucess ! " << endl;
  }
  
  if(pageGatheringByCurl(_FILEMY, (char*)URLLINK2.c_str()) != 1)
  	cout << "Totally Fail !" << endl;
  else
  {
  	//cout << "Sucess ! " << endl;
  }
  
  return 0;
}
