/*
	XML Parser main functions
*/

#include "xmlParser.h"

char *getUrlLists(char *_sourceXml)
{
	char *urlListsBuff;
	int urlListsBuffIndex = 0;
	int urlListsBuffSize = 0;
	
	int shiftNum = 0;					//For first shifting flag of buff
	int secondShiftNum = 0;		//For second shifting flag of buff
	string strBuff;
	
	urlListsBuffSize = strlen(_sourceXml);
	
	/*Malloc a block memory to buffer content.*/
	urlListsBuff = (char*)malloc(sizeof(char) * urlListsBuffSize);
	
	
	for(int buffIndex = 0; buffIndex < urlListsBuffSize; buffIndex++)
	{
		shiftNum = 0;
		secondShiftNum = 0;
		strBuff = "";
			
		/*--Parse tag "<A>"--*/
		if(_sourceXml[buffIndex] == '<')
		{
			shiftNum += 1;
			if(_sourceXml[buffIndex + shiftNum] == 'A')
			{
				shiftNum += 1;
				if(_sourceXml[buffIndex + shiftNum] == '>')
				{
					shiftNum+= 1;
					while(_sourceXml[buffIndex + shiftNum + secondShiftNum] != '<')
					{
						secondShiftNum++;
					}
					
					for(int len = 0; len < secondShiftNum; len++)
						strBuff += _sourceXml[buffIndex + shiftNum + len];
					strBuff += "\n";
										
					memcpy(&urlListsBuff[urlListsBuffIndex], strBuff.c_str(), secondShiftNum + 1);
					urlListsBuffIndex = urlListsBuffIndex + secondShiftNum + 1;
				}
			}
			buffIndex = buffIndex + shiftNum + secondShiftNum;			
		}
		
		/*--Parse tag "<IMG>"--*/
		if(_sourceXml[buffIndex] == '<')
		{
			shiftNum += 1;
			if(_sourceXml[buffIndex + shiftNum] == 'I')
			{
				shiftNum += 1;
				if(_sourceXml[buffIndex + shiftNum] == 'M')
				{
					shiftNum += 1;
					if(_sourceXml[buffIndex + shiftNum] == 'G')
					{
						if(_sourceXml[buffIndex + shiftNum] == '>')
						{
							shiftNum+= 1;
							while(_sourceXml[buffIndex + shiftNum + secondShiftNum] != '<')
							{
								secondShiftNum++;
							}
							
							for(int len = 0; len < secondShiftNum; len++)
								strBuff += _sourceXml[buffIndex + shiftNum + len];
							strBuff += "\n";
												
							memcpy(&urlListsBuff[urlListsBuffIndex], strBuff.c_str(), secondShiftNum + 1);
							urlListsBuffIndex = urlListsBuffIndex + secondShiftNum + 1;
						}
					}
				}
			}
			buffIndex = buffIndex + shiftNum + secondShiftNum;			
		}
		
		/*--Parse tag "<BASE>"--*/
		if(_sourceXml[buffIndex] == '<')
		{
			shiftNum += 1;
			if(_sourceXml[buffIndex + shiftNum] == 'B')
			{
				shiftNum += 1;
				if(_sourceXml[buffIndex + shiftNum] == 'A')
				{
					shiftNum += 1;
					if(_sourceXml[buffIndex + shiftNum] == 'S')
					{
						shiftNum += 1;
						if(_sourceXml[buffIndex + shiftNum] == 'E')
						{
							shiftNum += 1;
							if(_sourceXml[buffIndex + shiftNum] == '>')
							{
								shiftNum+= 1;
								while(_sourceXml[buffIndex + shiftNum + secondShiftNum] != '<')
								{
									secondShiftNum++;
								}
								
								for(int len = 0; len < secondShiftNum; len++)
									strBuff += _sourceXml[buffIndex + shiftNum + len];
								strBuff += "\n";
													
								memcpy(&urlListsBuff[urlListsBuffIndex], strBuff.c_str(), secondShiftNum + 1);
								urlListsBuffIndex = urlListsBuffIndex + secondShiftNum + 1;
							}
						}
					}
				}				
			}
			buffIndex = buffIndex + shiftNum + secondShiftNum;			
		}
		
		/*--Parse tag "<FORM>"--*/
		if(_sourceXml[buffIndex] == '<')
		{
			shiftNum += 1;
			if(_sourceXml[buffIndex + shiftNum] == 'F')
			{
				shiftNum += 1;
				if(_sourceXml[buffIndex + shiftNum] == 'O')
				{
					shiftNum += 1;
					if(_sourceXml[buffIndex + shiftNum] == 'R')
					{
						shiftNum += 1;
						if(_sourceXml[buffIndex + shiftNum] == 'M')
						{
							shiftNum += 1;
							if(_sourceXml[buffIndex + shiftNum] == '>')
							{
								shiftNum+= 1;
								while(_sourceXml[buffIndex + shiftNum + secondShiftNum] != '<')
								{
									secondShiftNum++;
								}
								
								for(int len = 0; len < secondShiftNum; len++)
									strBuff += _sourceXml[buffIndex + shiftNum + len];
								strBuff += "\n";
													
								memcpy(&urlListsBuff[urlListsBuffIndex], strBuff.c_str(), secondShiftNum + 1);
								urlListsBuffIndex = urlListsBuffIndex + secondShiftNum + 1;
							}
						}
					}
				}				
			}
			buffIndex = buffIndex + shiftNum + secondShiftNum;			
		}
		
		/*--Parse tag "<LINK>"--*/
		if(_sourceXml[buffIndex] == '<')
		{
			shiftNum += 1;
			if(_sourceXml[buffIndex + shiftNum] == 'L')
			{
				shiftNum += 1;
				if(_sourceXml[buffIndex + shiftNum] == 'I')
				{
					shiftNum += 1;
					if(_sourceXml[buffIndex + shiftNum] == 'N')
					{
						shiftNum += 1;
						if(_sourceXml[buffIndex + shiftNum] == 'K')
						{
							shiftNum += 1;
							if(_sourceXml[buffIndex + shiftNum] == '>')
							{
								shiftNum+= 1;
								while(_sourceXml[buffIndex + shiftNum + secondShiftNum] != '<')
								{
									secondShiftNum++;
								}
								
								for(int len = 0; len < secondShiftNum; len++)
									strBuff += _sourceXml[buffIndex + shiftNum + len];
								strBuff += "\n";
													
								memcpy(&urlListsBuff[urlListsBuffIndex], strBuff.c_str(), secondShiftNum + 1);
								urlListsBuffIndex = urlListsBuffIndex + secondShiftNum + 1;
							}
						}
					}
				}				
			}
			buffIndex = buffIndex + shiftNum + secondShiftNum;			
		}
		
		/*--Parse tag "<SCRIPT>"--*/
		if(_sourceXml[buffIndex] == '<')
		{
			shiftNum += 1;
			if(_sourceXml[buffIndex + shiftNum] == 'S')
			{
				shiftNum += 1;
				if(_sourceXml[buffIndex + shiftNum] == 'C')
				{
					shiftNum += 1;
					if(_sourceXml[buffIndex + shiftNum] == 'R')
					{
						shiftNum += 1;
						if(_sourceXml[buffIndex + shiftNum] == 'I')
						{
							shiftNum += 1;
							if(_sourceXml[buffIndex + shiftNum] == 'P')
							{
								shiftNum += 1;
								if(_sourceXml[buffIndex + shiftNum] == 'T')
								{
									shiftNum += 1;
									if(_sourceXml[buffIndex + shiftNum] == '>')
									{
										shiftNum+= 1;
										while(_sourceXml[buffIndex + shiftNum + secondShiftNum] != '<')
										{
											secondShiftNum++;
										}
										
										for(int len = 0; len < secondShiftNum; len++)
											strBuff += _sourceXml[buffIndex + shiftNum + len];
										strBuff += "\n";
															
										memcpy(&urlListsBuff[urlListsBuffIndex], strBuff.c_str(), secondShiftNum + 1);
										urlListsBuffIndex = urlListsBuffIndex + secondShiftNum + 1;
									}
								}
							}							
						}
					}
				}				
			}
			buffIndex = buffIndex + shiftNum + secondShiftNum;			
		}
		
		/*--Parse tag "<IFRAME>"--*/
		if(_sourceXml[buffIndex] == '<')
		{
			shiftNum += 1;
			if(_sourceXml[buffIndex + shiftNum] == 'I')
			{
				shiftNum += 1;
				if(_sourceXml[buffIndex + shiftNum] == 'F')
				{
					shiftNum += 1;
					if(_sourceXml[buffIndex + shiftNum] == 'R')
					{
						shiftNum += 1;
						if(_sourceXml[buffIndex + shiftNum] == 'A')
						{
							shiftNum += 1;
							if(_sourceXml[buffIndex + shiftNum] == 'M')
							{
								shiftNum += 1;
								if(_sourceXml[buffIndex + shiftNum] == 'E')
								{
									shiftNum += 1;
									if(_sourceXml[buffIndex + shiftNum] == '>')
									{
										shiftNum+= 1;
										while(_sourceXml[buffIndex + shiftNum + secondShiftNum] != '<')
										{
											secondShiftNum++;
										}
										
										for(int len = 0; len < secondShiftNum; len++)
											strBuff += _sourceXml[buffIndex + shiftNum + len];
										strBuff += "\n";
															
										memcpy(&urlListsBuff[urlListsBuffIndex], strBuff.c_str(), secondShiftNum + 1);
										urlListsBuffIndex = urlListsBuffIndex + secondShiftNum + 1;
									}
								}
							}							
						}
					}
				}				
			}
			buffIndex = buffIndex + shiftNum + secondShiftNum;
		}
		
	}
	
	
	return urlListsBuff;
	
}
