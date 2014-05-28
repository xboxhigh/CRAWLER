#include "pageGathering.h"

int main()
{
	FInfo FILEVAR;
	Offset OFFSET;
	OFFSET.BegHOffset = 0;
	OFFSET.EndHOffset = 0;
	OFFSET.BegCOffset = 0;
	OFFSET.EndCOffset = 0;
	
	string headerFileName = "/data2/xboxhigh/_gatheringFiles/hFile/header.";
  string bodyFileName = "/data2/xboxhigh/_gatheringFiles/bFile/body.";
  string oriHBOffsetFileName = "/data2/xboxhigh/_gatheringFiles/oFile/oriHBOffset.";
  
  FILEVAR.Header = fopen(headerFileName.c_str(), "w+");
	 	if (FILEVAR.Header == NULL) cout << "No Such Path" << endl;
	FILEVAR.Content = fopen(bodyFileName.c_str(), "w+");
		if (FILEVAR.Content == NULL) cout << "No Such Path" << endl;
	FILEVAR.OriOffset = fopen(oriHBOffsetFileName.c_str(), "w+");
		if (FILEVAR.OriOffset == NULL) cout << "No Such Path" << endl;
			
	char str[1024];
	strcat(str, "http://www.ultraedit.com/downloads/extras.html#wordfiles");
	
	pageGatheringByCurl(str, FILEVAR);
	getFileOffset(FILEVAR, OFFSET, str);
	
	fclose(FILEVAR.Header);
	fclose(FILEVAR.Content);
	
	return 1;
}
