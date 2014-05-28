#include "pageGathering.h"
#include "globalFunc.h"


int main()
{
	FInfo FILEVAR, _file;
	
	//Read Files//
	char seedsFileName[128];	
	bzero(&seedsFileName, sizeof(seedsFileName));
	strcpy(seedsFileName, "/data2/xboxhigh/_gatheringFiles/pFile/URLLists");
	
	//Write Files//	
	char headerFileName[128];
	char contentFileName[128];
	bzero(&headerFileName, sizeof(headerFileName));
	bzero(&contentFileName, sizeof(contentFileName));
	strcpy(headerFileName, "Header.");
	strcpy(contentFileName, "Content.");
	
	FILEVAR.Header = fopen(headerFileName, "w+");
	if (FILEVAR.Header == NULL) cout << "No Such Path [" << headerFileName << "]" << endl;
	FILEVAR.Content = fopen(contentFileName, "w+");
	if (FILEVAR.Content == NULL) cout << "No Such Path [" << contentFileName << "]" << endl;
	FILEVAR.DistributedSeeds = fopen(seedsFileName, "r");
	if (FILEVAR.DistributedSeeds == NULL) cout << "No Such Path [" << seedsFileName << "]" << endl;
		
	//cout << "OK !  This is Child Process and PID : " << curID << endl;
	//cout << "Process " << curID << " start gathering web pages..." << endl;
	
	//Begin gathering web pages//				
	char Line[10 * 1024];
	char *find = 0;
	
	Offset OFFSET;
	OFFSET.BegOffset = 0;
	OFFSET.EndOffset = 0;
	OFFSET.BegCOffset = 0;
	OFFSET.EndCOffset = 0;
	int key = 0;
	
	cout << "Start gathering web pages..."<< endl;
	
	while(fgets(Line, 10 * 1024 - 1, FILEVAR.DistributedSeeds))
	{				
		if ((find = strrchr(Line, '\n')))
		{
			*find = '\0';
			cout << "URL : " << Line << endl;
			if(pageGatheringByCurl(FILEVAR, Line, OFFSET) != 1)
			{
  			cout << "Totally Fail !" << endl;
  		}
		}
		key++;
	}
	
	
	//cout << "Process " << curID << " URL COUNT : " << key << endl;
	
	//Write Result into the Original Offset File//		
				
	fclose(FILEVAR.Header);
	fclose(FILEVAR.Content);
	fclose(FILEVAR.DistributedSeeds);
	
	cout << "Finish gathering !" << endl;
	
}


