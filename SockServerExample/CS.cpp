#include "CS.hpp"
#include "Main.hpp"
#include "Hash.hpp"
#include <ctype.h>
#include <stdio.h>

char	g_pszCSFile[1024];

bool LoadCS(char *pszFileName)
{
	FILE		*fpCS;
	SHashNode	*spNode=NULL;
	char		czBuffer[LINE_BUF_LEN+1];

	strcpy(g_pszCSFile,pszFileName);
	if( (fpCS=fopen(pszFileName,"r")) == NULL )
		return false;
	while( fgets(czBuffer,LINE_BUF_LEN,fpCS) )
	{
		if( strlen(czBuffer)==33 )
		{
			spNode=(SHashNode *)Memory->Malloc(sizeof(SHashNode));
			asc2bin(czBuffer,32,(char *)spNode->pszSignature);
			Hash->Insert(spNode);
			spNode->cFlag=0;
		}
	}
	fclose(fpCS);
	return true;
}