#include "pageGathering.h"

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
 		//memcpy(&_tar[_tarIndex], tmpDeli.c_str(), tmpDeli.length());
 		//_tarIndex = _tarIndex + tmpDeli.length();	
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
 		//memcpy(&_tar[_tarIndex], tmpDeli.c_str(), tmpDeli.length());
 		//_tarIndex = _tarIndex + tmpDeli.length();	
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
 		//memcpy(&_tar[_tarIndex], tmpDeli.c_str(), tmpDeli.length());
 		//_tarIndex = _tarIndex + tmpDeli.length();	
 		
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
 		//memcpy(&_tar[_tarIndex], tmpDeli.c_str(), tmpDeli.length());
 		//_tarIndex = _tarIndex + tmpDeli.length();	
 		
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

int writeHeaderMetaData(HeaderInfo *_CurlInfo, CURL *_curl_handle, MemoryStruct *_header, FILE *_file)
{
	string tmpDeli = "\0";
	char *metaHeaderBuff;
	int divisionResl = 0;
	int shiftIndex = 0;
	int code = 0;
	char *err;
	
	char *CURLINFO_RedirURL;
	char *CURLINFO_ContentType;
	
	metaHeaderBuff = (char*)malloc(sizeof(char) * 1024 * 1024);
				
 	code = curl_easy_getinfo(_curl_handle, CURLINFO_RESPONSE_CODE, &_CurlInfo->CURLINFO_RepCode);
 	
	if((CURLE_OK ==	code) && ((_CurlInfo->CURLINFO_RepCode / 100) != 4))
 	{
 		char str[4];
 		itoa(_CurlInfo->CURLINFO_RepCode, str);
 		
 		memcpy(&metaHeaderBuff[shiftIndex], "<sCode>", 7);
 		shiftIndex = shiftIndex + 7;
 		memcpy(&metaHeaderBuff[shiftIndex], str, strlen(str));
 		shiftIndex = shiftIndex + strlen(str);
 		memcpy(&metaHeaderBuff[shiftIndex], "</sCode>", 8);
 		shiftIndex = shiftIndex + 8;
 		//memcpy(&metaHeaderBuff[shiftIndex], tmpDeli.c_str(), tmpDeli.length());
 		//shiftIndex = shiftIndex + tmpDeli.length();	
			
		if(CURLE_OK ==
			curl_easy_getinfo(_curl_handle, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &_CurlInfo->CURLINFO_ContentLen))
		{
	 		char str[128];
	 		itoa(_CurlInfo->CURLINFO_ContentLen, str);
	 		
			memcpy(&metaHeaderBuff[shiftIndex], "<cLen>", 6);
	 		shiftIndex = shiftIndex + 6;
	 		memcpy(&metaHeaderBuff[shiftIndex], str, strlen(str));
	 		shiftIndex = shiftIndex + strlen(str);
	 		memcpy(&metaHeaderBuff[shiftIndex], "</cLen>", 7);
	 		shiftIndex = shiftIndex + 7;
	 		//memcpy(&metaHeaderBuff[shiftIndex], tmpDeli.c_str(), tmpDeli.length());
	 		//shiftIndex = shiftIndex + tmpDeli.length();	
		}
		
	 	if((CURLE_OK ==
			curl_easy_getinfo(_curl_handle, CURLINFO_REDIRECT_URL, &CURLINFO_RedirURL))
			&& CURLINFO_RedirURL)
		{					
			memcpy(&metaHeaderBuff[shiftIndex], "<reUrl>", 7);
	 		shiftIndex = shiftIndex + 7;
	 		memcpy(&metaHeaderBuff[shiftIndex], CURLINFO_RedirURL,
	 						strlen(CURLINFO_RedirURL));
	 		shiftIndex = shiftIndex + strlen(CURLINFO_RedirURL);
	 		memcpy(&metaHeaderBuff[shiftIndex], "</reUrl>", 8);
	 		shiftIndex = shiftIndex + 8;
	 		//memcpy(&metaHeaderBuff[shiftIndex], tmpDeli.c_str(), tmpDeli.length());
	 		//shiftIndex = shiftIndex + tmpDeli.length();	
		}
		if((CURLE_OK ==
			curl_easy_getinfo(_curl_handle, CURLINFO_CONTENT_TYPE, &CURLINFO_ContentType))
			&& CURLINFO_ContentType)
		{
			memcpy(&metaHeaderBuff[shiftIndex], "<cType>", 7);
	 		shiftIndex = shiftIndex + 7;
	 		memcpy(&metaHeaderBuff[shiftIndex], CURLINFO_ContentType, 
	 						strlen(CURLINFO_ContentType));
	 		shiftIndex = shiftIndex + strlen(CURLINFO_ContentType);
	 		memcpy(&metaHeaderBuff[shiftIndex], "</cType>", 8);
	 		shiftIndex = shiftIndex + 8;
	 		//memcpy(&metaHeaderBuff[shiftIndex], tmpDeli.c_str(), tmpDeli.length());
	 		//shiftIndex = shiftIndex + tmpDeli.length();	
		}		
		
	}
	else
	{
		cout << "Add tag error" << endl;
		return 0;
	}
	
/*
	cout << endl << "========Original====================" << endl;
 	cout << _header.memory << endl;
 	*/
 	
	addTagInHeaderMetaData(_header->memory, metaHeaderBuff, shiftIndex);

 	/*
	cout << "=============Combinition===============" << endl;
	cout << "{"<< shiftIndex << "}" << endl;
	cout << metaHeaderBuff << endl;
	*/
	
	fwrite(metaHeaderBuff, 1, shiftIndex, _file);
	fflush(_file);
	
	free(metaHeaderBuff);
	
	return 1;
}

//Gather Web Pages by CURL Lib//
int pageGatheringByCurl(FInfo *_file, char *_url, Offset *_OFFSET)
{
	CURL *curl_handle;
	CURLcode code;
	HeaderInfo CurlInfo;
	size_t writeSize;
	
	struct MemoryStruct Header;
 	struct MemoryStruct Content;
 	
 	char *err;
	
  Header.memory = (char*)malloc(sizeof(char) * 128 * 1024);  /* will be grown as needed by the realloc above */ 
  Header.size = 0;    /* no data at this point */ 
  Content.memory = (char*)malloc(sizeof(char) * 128 * 1024);  /* will be grown as needed by the realloc above */ 
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
	
 	if(CURLE_OK == curl_easy_perform(curl_handle))
 	{
 		if(writeHeaderMetaData(&CurlInfo, curl_handle, &Header, _file->Header) != 0)
 		{
 			//cout << Content.size << endl;
 			//fputs(Content.memory, _file.Content);

 			writeSize = fwrite(Content.memory, 1, Content.size,  _file->Content);
 			fflush(_file->Content);

			cout << "Really write size : " << writeSize <<", Content size : " << Content.size << endl;
 			
 			if(CurlInfo.CURLINFO_ContentLen != -1)
 			{
	 			if(_OFFSET->BegCOffset == 0 )
	 			{	 				
	 				_OFFSET->EndCOffset = CurlInfo.CURLINFO_ContentLen;
	 			}
	 			else
	 			{
	 				_OFFSET->BegCOffset = _OFFSET->EndCOffset;
					_OFFSET->EndCOffset = _OFFSET->BegCOffset + CurlInfo.CURLINFO_ContentLen;
	 			}
 			}
 			else
 			{
 				if(_OFFSET->BegCOffset == 0)
	 			{
	 				_OFFSET->EndCOffset = ftell(_file->Content);
	 			}
	 			else
	 			{
	 				_OFFSET->BegCOffset = _OFFSET->EndCOffset;
					_OFFSET->EndCOffset = _OFFSET->BegCOffset + Content.size;
					fseek(_file->Content, _OFFSET->BegCOffset , SEEK_SET);
	 			}
 			}
 			
 			_OFFSET->BegOffset = _OFFSET->BegCOffset;
	 		_OFFSET->EndOffset = _OFFSET->EndCOffset;
	 		
			/*Let Begin Offset point be current End Offset*/
			_OFFSET->BegCOffset = _OFFSET->EndCOffset;
 		}
 		else
 		{
 			cout << "Page not found (40X) !" << endl;
 			return 0;
 		}
 	}
	else
	{
		cout << "CURL ERROR ! [" << err << "]" << endl;
		return 0;
	}
  /* cleanup curl stuff */
  
  
 	free(Header.memory);
 	free(Content.memory);
	
	return 1;
}
