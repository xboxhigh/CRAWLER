#ifndef CRAWLERNORM_H
#define CRAWLERNORM_H


#include <iostream>
#include <curl/curl.h>
#include <string>
#include <vector>
#include <pthread.h>

#define NUMT 4

using namespace std;

class CRAWLER	{
private:
	void Init(string _hFilePath, string _cFilePath, string _mFilePath);
	void* PullOneURL(void* _url);
	
	
	string hFilePath;
	string cFilePath;
	string mFilePath;
public:
	CRAWLER(string _hFilePath, string _cFilePath, string _mFilePath);
	~CRAWLER() {}
	
	int FetchPagesInMultiThread(vector<string> _urlList);
	void SetFilePath(string _hp, string _cp, string _mp);
	vector<string> GetURLLists(string _path);
};

#endif  // ifndef CRAWLERNORM_H //