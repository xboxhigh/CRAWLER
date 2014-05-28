/*
	Main idea, separate the http header file and the content file.
And we need to store another file, called metadata, including the most important header information
and the offset of header file and content file.
	
*/

#include "CrawlerNorm.h"

int main(int argc, char **argv)	{
	
	string pHeader = "";
	string pContent = "";
	string pMetadata = "";
	string pURLList = "";
	
	CRAWLER CRAWL(pHeader, pContent, pMetadata);
	
	vector<string> URLList;
	URLList = vector<string>();
	URLList = GetURLLists(pURLList);
	
	CRAWL.FetchPagesInMultiThread(URLList);
	
	return 0;
}