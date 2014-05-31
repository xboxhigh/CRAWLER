#ifndef CRAWLERNORM_H
#define CRAWLERNORM_H


#include <iostream>
#include <curl/curl.h>
#include <string>
#include <vector>
#include <pthread.h>
#include <fstream>

#define NUMT 1				//Number of threads

using namespace std;

class CRAWLER	{
private:
	void Init(string _hFilePath, string _cFilePath, string _mFilePath);
	void* PullOneURL(void* _url);
	
	
	string hFilePath;
	string cFilePath;
	string mFilePath;
	string hBuff;		//	HTTP header buffer
	string cBuff;		//	HTTP content buffer
	int cBegOffset;
	int cEndOffset;
public:
	CRAWLER(string _hFilePath, string _cFilePath, string _mFilePath);
	~CRAWLER() {}
	
	int FetchPagesInMultiThread(vector<string> _urlList);
	
	void SetFilePath(string _hp, string _cp, string _mp);
	vector<string> GetURLLists(string _path);
	void ResetHBuff()	{	hBuff.clear();}
	void ResetCBuff()	{	cBuff.clear();}
};

#endif  // ifndef CRAWLERNORM_H //