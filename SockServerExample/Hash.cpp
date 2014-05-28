#include "Hash.hpp"
#include <string.h>

THash::THash(unsigned int uiTS)
{
	sapHashTable=new (SHashNode *)[uiTS];
	bzero(sapHashTable, sizeof(SHashNode *)*uiTS );
	uiTableSize=uiTS;
}


unsigned int THash::Sig2HV(unsigned char *pszSig)
{
        unsigned int    n,i;

        n=0;
        for(i=0;i<16;i++)
                n=((n<<2)|(pszSig[i]&0x03));
        return (n%uiTableSize);
}

bool THash::Insert(SHashNode *spNode)
{
	unsigned int	uiHV;
	
	uiHV=Sig2HV(spNode->pszSignature);
	spNode->spNext=sapHashTable[uiHV];
	sapHashTable[uiHV]=spNode;
	
}

SHashNode *THash::Query(unsigned char *pszSignature)
{
	unsigned int	uiHV;
	SHashNode		*spNode;
	
	uiHV=Sig2HV(pszSignature);
	spNode=sapHashTable[uiHV];
	while( spNode )
	{
		if( memcmp(pszSignature, spNode->pszSignature, 16) == 0 )
			return spNode;
		spNode=spNode->spNext;
	}
	return NULL;
}

THash::~THash()
{
	delete sapHashTable;
}