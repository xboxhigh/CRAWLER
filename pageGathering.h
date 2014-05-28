#ifndef PAGEGATHERING_H 
#define PAGEGATHERING_H 

#include <curl.h>
#include <queue>
#include <dirent.h>
#include <string>

#include "globalFunc.h"

struct MemoryStruct 
{
  char *memory;
  size_t size;
};

struct HeaderInfo
{	
	long CURLINFO_RepCode;
	double CURLINFO_ContentLen;
};

using namespace std;

int pageGatheringByCurl(FInfo *_file, char *_url, Offset *_OFFSET);
int writeHeaderMetaData(HeaderInfo *_CurlInfo, CURL *_curl_handle, MemoryStruct *_header, FILE *_file);
int addTagInHeaderMetaData(char *_src, char *_tar, int &_tarIndex);
void extractHeaderData(string _src, char *_tar, int &_tarIndex);
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);
static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream);

#endif  /* #ifndef PAGEGATHERING_H */ 
