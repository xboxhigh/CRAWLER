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
	
	// Step1. Get URL Seeds
	URLList = vector<string>();
	URLList = CRAWL.GetURLLists(pURLList);
	URLList.push_back("http://www.easytravel.com.tw/member/default.aspx?go=");
	//URLList.push_back("http://www.easytravel.com.tw/member/Login.aspx?go=&login=y");	
	URLList.push_back("https://www.facebook.com/qiang.min?ref=tn_tnmn");
	URLList.push_back("http://www2.eyny.com/thread-9565775-1-3DN3CFFH.html");
	
	// Step2. Start gathering the web pages
	CRAWL.FetchPagesInSingleThread(URLList);
	
	// Step3. Write web pages' header and content information separate.
	
	return 0;
}
