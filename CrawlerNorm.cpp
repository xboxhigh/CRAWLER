#include "CrawlerNorm.h"

CRAWLER::CRAWLER(string _hFilePath, string _cFilePath, string _mFilePath)	{
	Init(_hFilePath, _cFilePath, _mFilePath);
}

void CRAWLER::Init(string _hFilePath, string _cFilePath, string _mFilePath)	{
	SetFilePath(_hFilePath, _cFilePath, _mFilePath);
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
	
	fin.open(path.c_str(), ios::in);
	
	while(fin.getline(buffer, sizeof(buffer),'\n'))	{
	
		_urlListBuff.push_back(buffer);
	}
	
	return _urlListBuff;
}

void* CRAWLER::PullOneURL(void* _url)	{
  
  CURL *curl; 
  
  curl = curl_easy_init();
  curl_easy_setopt(curl, CURLOPT_URL, _url);
  curl_easy_perform(curl); /* ignores error */ 
  curl_easy_cleanup(curl);
 
  return NULL;
}

int CRAWLER::FetchPagesInMultiThread(vector<string> _urlList)	{
	
	for (vector<string>::iterator it = _urlList.begin() ;it != _urlList.end(); ++it)	{		
		//std::cout << ' ' << *it;		
		//fputs(&*it->c_str(), LinkFile);
		//fputs("\n", LinkFile);
	
	
	
	
	
	}
	
	return 0;
}
