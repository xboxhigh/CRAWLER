#include "CrawlerNorm.h"

/// Write HTML data into a string
static size_t WriteCallback(char* _src, size_t size, size_t nmemb, string* _tar)
{	
	size_t realsize = 0;
	
	if(_tar != NULL)	{
		_tar->append(_src, size * nmemb);
		realsize = size * nmemb;
	}

	return realsize;
}

CRAWLER::CRAWLER(string _hFilePath, string _cFilePath, string _mFilePath)	{
	Init(_hFilePath, _cFilePath, _mFilePath);
}

void CRAWLER::Init(string _hFilePath, string _cFilePath, string _mFilePath)	{
	SetFilePath(_hFilePath, _cFilePath, _mFilePath);
	
	hBuff = "";
	cBuff = "";
}

void CRAWLER::SetFilePath(string _hp, string _cp, string _mp)	{
	hFilePath = _hp;
	cFilePath = _cp;
	mFilePath = _mp;
}

vector<string> CRAWLER::GetURLLists(string _path)	{
	char buffer[1024];	
	fstream fin;
	vector<string> _urlListBuff = vector<string>();
	
	fin.open(_path.c_str(), ios::in);
	
	while(fin.getline(buffer, sizeof(buffer),'\n'))	{
	
		_urlListBuff.push_back(buffer);
	}
	
	return _urlListBuff;
}

void* CRAWLER::PullOneURL(void* _url)	{
  
	CURL *curl_handle; 
	char *err;
	
	curl_global_init(CURL_GLOBAL_ALL);
	// init the curl session // 
	curl_handle = curl_easy_init(); 
	// set URL to get // 
	curl_easy_setopt(curl_handle, CURLOPT_URL, _url); 
	// no progress meter please // 
	curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);
	// Write HTML data into a string //
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteCallback);
	// we want the headers to this file handle //
	curl_easy_setopt(curl_handle, CURLOPT_WRITEHEADER, &hBuff);	
	// write the body to this file handle //
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &cBuff);
	
	curl_easy_setopt(curl_handle, CURLOPT_ERRORBUFFER, &err);
	
	curl_easy_perform(curl_handle);

	//curl_easy_perform(curl_handle); /* ignores error */ 
	curl_easy_cleanup(curl_handle);
	
	return NULL;
}

int CRAWLER::FetchPagesInMultiThread(vector<string> _urlList)	{
	
	ResetHBuff();
	ResetCBuff();
	
	for (unsigned int index = 0; index < _urlList.size(); index++)	{
		
		//cout << _urlList[index] << endl;
		// Save header information and content information in hBuff, bBuff
		PullOneURL((void* const)_urlList[index].c_str());
		// Write Raw content in file
		
		// Keep important information in metadata file
		
		
		
	}
	
	return 0;
}
