#include "urlExtracting.h"

string replaceCharacter(char _char)
{
	string repStr;
	
	if(_char == '&')
		repStr = "$amp;";
	else if(_char == '\"')
		repStr = "&quot;";
	else if(_char == '\'')
		repStr = "&apos;";
	else if(_char == '<')
		repStr = "&lt;";
	else if(_char == '>')
		repStr = "&gt;";
	else
		repStr = _char;
	//cout << "(\'" << repStr << "\')"<< endl;
	return repStr;

}

int checkTypePerLink(IndexNums *_Index, char *_src, char *_tar)
{
	if(_src[_Index->pivot + _Index->firstShiftIndex + _Index->secondShiftIndex] == '\"')
	{
		_Index->secondShiftIndex += 1;
		while(_src[_Index->pivot + _Index->firstShiftIndex + _Index->secondShiftIndex] != '\"')
		{
			strcat(_tar, replaceCharacter(_src[_Index->pivot + _Index->firstShiftIndex + _Index->secondShiftIndex]).c_str());
			_Index->secondShiftIndex++;
			_Index->tarIndex++;
			
			if(_Index->secondShiftIndex > 1024)
				break;
		}
	}
	else if(_src[_Index->pivot + _Index->firstShiftIndex + _Index->secondShiftIndex] == '\'')
	{
		_Index->secondShiftIndex += 1;
		while(_src[_Index->pivot + _Index->firstShiftIndex + _Index->secondShiftIndex] != '\'')
		{
			strcat(_tar, replaceCharacter(_src[_Index->pivot + _Index->firstShiftIndex + _Index->secondShiftIndex]).c_str());
			_Index->secondShiftIndex++;
			_Index->tarIndex++;
			
			if(_Index->secondShiftIndex > 1024)
				break;
		}
	}
	else
	{
		while(_src[_Index->pivot + _Index->firstShiftIndex + _Index->secondShiftIndex] != '>')
		{
			strcat(_tar, replaceCharacter(_src[_Index->pivot + _Index->firstShiftIndex + _Index->secondShiftIndex]).c_str());
			_Index->secondShiftIndex++;
			_Index->tarIndex++;
			
			if(_Index->secondShiftIndex > 1024)
				break;
		}
	}
	//cout << _tar.length() << " ) " << _tar << endl;
	return 1;
}

int CombinationTags(FILE *_file, char *_src, char _tagType)
{
	switch(_tagType)
	{
	case 'i':					//<img tag//
		fputs("<im>", _file);
		fwrite(_src, 1, strlen(_src), _file);
		fputs("</im>", _file);
		break;
	case 'b':					//<base tag//
		fputs("<ba>", _file);
		fwrite(_src, 1, strlen(_src), _file);
		fputs("</ba>", _file);
		break;
	case 'a':					//<a href tag//
		fputs("<ah>", _file);
		fwrite(_src, 1, strlen(_src), _file);
		fputs("</ah>", _file);
		break;
	case 'l':					//<link tag//
		fputs("<li>", _file);
		fwrite(_src, 1, strlen(_src), _file);
		fputs("</li>", _file);
		break;
	case 'f':					//form tag//
		fputs("<fo>", _file);
		fwrite(_src, 1, strlen(_src), _file);
		fputs("</fo>", _file);
		break;
	case 'r':					//<iframe tag//
		fputs("<if>", _file);
		fwrite(_src, 1, strlen(_src), _file);
		fputs("</if>", _file);
		break;
	}	
	return 1;	
}

int CombinationWithBaseURL(char *_baseURL, char *_tar)
{
	char buffStr[1024];
	int pivot = 0;
	
	bzero(&buffStr, sizeof(buffStr));
	
	if((_tar[0] == '#' && strlen(_tar) > 1) || (_tar[0] == '/' && strlen(_tar) > 1))
	{		
		memcpy(buffStr, _baseURL, strlen(_baseURL) + 1);
		
		if(_baseURL[strlen(_baseURL)] != '/')
		{
			strcat(buffStr, "/");
			buffStr[strlen(buffStr) + 1] = '\0';
		}
		memcpy(&buffStr[strlen(buffStr)], &_tar[1], strlen(_tar) + 1);
		buffStr[strlen(buffStr) + 1] = '\0';
		
		memcpy(_tar, buffStr, strlen(buffStr));
		_tar[strlen(_tar) + 1] = '\0';
		
	}
	else if((_tar[0] == '#' && strlen(_tar) == 1) || (_tar[0] == '/' && strlen(_tar) == 1))
	{
		memcpy(_tar, _baseURL, strlen(_baseURL));
		pivot += strlen(_baseURL);
		memcpy(&_tar[pivot], "\0", 1);
		pivot++;
		
		_tar[strlen(_tar) + 1] = '\0';
	}
	else if(_tar[0] != 'h' && _tar[1] != 't' && _tar[2] != 't' && _tar[3] != 'p' && strlen(_tar) > 1)
	{
		memcpy(&buffStr[pivot], _baseURL, strlen(_baseURL));
		pivot += strlen(_baseURL);
		memcpy(&buffStr[pivot], "\0", 1);
		pivot++;
		
		if(_baseURL[strlen(_baseURL)] != '/')
		{
			strcat(buffStr, "/");
			buffStr[pivot + 1] = '\0';
			pivot++;
		}
		
		memcpy(&buffStr[pivot], _tar, strlen(_tar));
		pivot += strlen(_tar);
		memcpy(&buffStr[pivot], "\0", 1);
		pivot++;
		
		memcpy(_tar, buffStr, strlen(buffStr) + 1);
	}
	else
		return 1;
	
	return 1;
}

int CheckBaseLinks(char *_contentBuff, char *_baseURL)
{	
	int buffSize = strlen(_contentBuff);
	bool baseURLTriger = false;
	char cache[128];
	
	IndexNums Index;
	
	Index.firstShiftIndex = 0;
	Index.secondShiftIndex = 0;
	Index.tarIndex = 0;
	Index.pivot = 0;
	
	bzero(&cache, sizeof(cache));
	
	//Setup baseURL//
	while(Index.pivot < buffSize)
	{
		Index.firstShiftIndex = 0;
		Index.secondShiftIndex = 0;
		
		if(_contentBuff[Index.pivot] == '<')
		{
			if(tolower(_contentBuff[Index.pivot + 1]) == 'b')
			{
				if(tolower(_contentBuff[Index.pivot + 2]) == 'a')
				{
					if(tolower(_contentBuff[Index.pivot + 3]) == 's')
					{
						if(tolower(_contentBuff[Index.pivot + 4]) == 'e')
						{							
							Index.firstShiftIndex += 5;
							
							while(Index.firstShiftIndex < buffSize)
							{
								if(tolower(_contentBuff[Index.pivot + Index.firstShiftIndex]) == 'h')
								{
									if(tolower(_contentBuff[Index.pivot + Index.firstShiftIndex + 1]) == 'r')
									{
										if(tolower(_contentBuff[Index.pivot + Index.firstShiftIndex + 2]) == 'e')
										{
											if(tolower(_contentBuff[Index.pivot + Index.firstShiftIndex + 3]) == 'f')
											{
												if(_contentBuff[Index.pivot + Index.firstShiftIndex + 4] == '=')
												{												
													if(_contentBuff[Index.pivot + Index.firstShiftIndex + 5] == '\"')
													{
														Index.secondShiftIndex = 6;
														
														while(_contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex] != '\"')
														{
															cache[Index.tarIndex] = _contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex];
															Index.secondShiftIndex++;
															Index.tarIndex++;
														}
														baseURLTriger = true;
														break;
													}
												
													else if(_contentBuff[Index.pivot + Index.firstShiftIndex + 5] == '\'')
													{
														Index.secondShiftIndex = 6;
														
														while(_contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex] != '\'')
														{
															cache[Index.tarIndex] = _contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex];
															Index.secondShiftIndex++;
															Index.tarIndex++;
														}
														baseURLTriger = true;
														break;
													}
													else
													{
														Index.secondShiftIndex = 5;
														
														while(_contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex] != '>')
														{
															cache[Index.tarIndex] = _contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex];
															Index.secondShiftIndex++;
															Index.tarIndex++;
														}
														baseURLTriger = true;								
														break;
													}
													cache[Index.tarIndex + 1] = '\0';
												}
											}
										}
									}
								}
								Index.firstShiftIndex++;
							}
							Index.pivot += Index.firstShiftIndex + Index.secondShiftIndex;
						}
					}
				}
			}
		}
		Index.pivot++;
	}
	
	
	if(baseURLTriger)
	{
		memcpy(_baseURL, cache, strlen(cache) + 1);
	}
	
	return 1;
}

int XMLParser(FInfo *_file, char *_OffsetBuff)
{
	int buffPerRead = 16 * 1024;
	int buffIndex = 0;
	char *contentBuff;
	char *scanKey;
	TagStr _TAG;
	
	contentBuff = (char*)malloc(sizeof(char) * buffPerRead);
	
	while(fgets(contentBuff, buffPerRead - 1, _file->Header))
	{
		contentBuff[buffPerRead] = '\0';
		
		for(int key = 0; key < buffPerRead; key++)
		{
			_TAG.fiveChr[0] = contentBuff[key];
			_TAG.fiveChr[1] = contentBuff[key + 1];
			_TAG.fiveChr[2] = contentBuff[key + 2];
			_TAG.fiveChr[3] = contentBuff[key + 3];
			_TAG.fiveChr[4] = contentBuff[key + 4];
			_TAG.fiveChr[5] = '\0';
			
			if(strcmp(_TAG.fiveChr, "<beg>") == 0)
			{
				key += 5;
								
				while(true)
				{
					if(contentBuff[key] != '<')
					{
						_TAG.begOffset += contentBuff[key];
						key++;
					}
					else
					{
						_TAG.begOffset += "\n";
						break;
					}
				}
				memcpy(&_OffsetBuff[buffIndex], _TAG.begOffset.c_str(), _TAG.begOffset.length());
				buffIndex += _TAG.begOffset.length();
				//cout << "Beg : " << _TAG.begOffset;
			}
			
			if(strcmp(_TAG.fiveChr, "<end>") == 0)
			{
				key += 5;
								
				while(true)
				{
					if(contentBuff[key] != '<')
					{
						_TAG.endOffset += contentBuff[key];
						key++;
					}
					else
					{
						_TAG.endOffset += "\n";
						break;
					}
				}
				memcpy(&_OffsetBuff[buffIndex], _TAG.endOffset.c_str(), _TAG.endOffset.length());
				buffIndex += _TAG.endOffset.length();
				//cout << "End : "<< _TAG.endOffset;
			}
			
			_TAG.begOffset = "";
			_TAG.endOffset = "";
		}
	}
	
	free(contentBuff);
	
	return 1;
}

int baseURLEx(FILE *_file, char *_tar)
{
	int buffPerRead = 128 * 1024 * 1024;
	char *contentBuff;
	
	int shift = 0;
	int pivot = 0;
	int buffIndex = 0;
	int eof = 0;
	int res = 0;
	
	contentBuff = (char*)malloc(sizeof(char) * buffPerRead);
	
	fseek(_file, 0, SEEK_END);
	eof = ftell(_file);
	rewind(_file);
	
  res = fread(contentBuff, 1, eof, _file);
	if(res != eof) {fputs ("Reading error (Func [baseURLEx] BUFF)\n", stderr);}
	
	cout << res << endl;
	while(pivot < eof)
	{
		if(contentBuff[pivot] == '<')
		{
			if(contentBuff[pivot + 1] == 'U')
			{
				if(contentBuff[pivot + 2] == 'R')
				{
					if(contentBuff[pivot + 3] == 'L')
					{
						if(contentBuff[pivot + 4] == '>')
						{
							shift = 5;
							while(contentBuff[pivot + shift] != '<')
							{
								memcpy(&_tar[buffIndex], &contentBuff[pivot + shift], 1);
								_tar[buffIndex] = contentBuff[pivot + shift];
								buffIndex++;
								shift++;
							}
							memcpy(&_tar[buffIndex], "\0", 1);
							buffIndex++;
							pivot += shift;
						}
					}
				}
			}
		}
		pivot++;
	}
	return 1;
}

int LinksExtracting(FILE *_file, char *_contentBuff, char *_baseURL, int _buffSize)
{
	//int buffSize = strlen(_contentBuff);
	
	IndexNums Index;
	
	Index.firstShiftIndex = 0;
	Index.secondShiftIndex = 0;
	Index.tarIndex = 0;
	Index.pivot = 0;
	
	//Check Base URL Link//
	cout <<"Before check base [" << _baseURL << "]" << endl;
	CheckBaseLinks(_contentBuff, _baseURL);	
	cout << "After check base [" << _baseURL << "]" << endl;
	
	//Check orther tags//
	while(Index.pivot < _buffSize)
	{
		Index.firstShiftIndex = 0;
		Index.secondShiftIndex = 0;
		Index.tarIndex = 0;
		char CacheOfURL[1024];
				
		if(_contentBuff[Index.pivot] == '<')
		{
			/*
			//Begin spliting <img src> tags & <iframe src>tags//	
			if(tolower(_contentBuff[Index.pivot + 1]) == 'i')
			{
				if(tolower(_contentBuff[Index.pivot + 2]) == 'm')
				{
					if(tolower(_contentBuff[Index.pivot + 3]) == 'g')
					{
						if(_contentBuff[Index.pivot + 4] == '=')
						{
							Index.firstShiftIndex = 5;
							while(Index.firstShiftIndex < _buffSize)
							{
								if(tolower(_contentBuff[Index.pivot + Index.firstShiftIndex]) == 's')
								{
									if(tolower(_contentBuff[Index.pivot + Index.firstShiftIndex + 1]) == 'r')
									{
										if(tolower(_contentBuff[Index.pivot + Index.firstShiftIndex + 2]) == 'c')
										{
											if(_contentBuff[Index.pivot + Index.firstShiftIndex + 3] == '=')
											{
												if(_contentBuff[Index.pivot + Index.firstShiftIndex + 4] == '\"')
												{
													Index.secondShiftIndex = 5;
													while(_contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex] != '\"' && Index.tarIndex < 1024)
													{
														//CacheOfURL[Index.tarIndex] = _contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex];
														memcpy(&CacheOfURL[Index.tarIndex], &_contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex], 1);
														Index.secondShiftIndex++;
														Index.tarIndex++;
													}
												}
												else if(_contentBuff[Index.pivot + Index.firstShiftIndex + 4] == '\'')
												{
													Index.secondShiftIndex = 5;
													while(_contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex] != '\'' && Index.tarIndex < 1024)
													{
														//CacheOfURL[Index.tarIndex] = _contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex];
														memcpy(&CacheOfURL[Index.tarIndex], &_contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex], 1);
														Index.secondShiftIndex++;
														Index.tarIndex++;
													}
												}
												else
												{
													Index.secondShiftIndex = 4;
													while(_contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex] != '>' && Index.tarIndex < 1024)
													{
														//CacheOfURL[Index.tarIndex] = _contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex];
														memcpy(&CacheOfURL[Index.tarIndex], &_contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex], 1);
														Index.secondShiftIndex++;
														Index.tarIndex++;
													}
												}
												//CacheOfURL[Index.tarIndex + 1] = '\0';
												memcpy(&CacheOfURL[Index.tarIndex], "\0", 1);
												Index.tarIndex++;
												CombinationWithBaseURL(_baseURL, CacheOfURL);
												CombinationTags(_file, CacheOfURL, 'i');
												break;
											}
										}
									}
								}
								Index.firstShiftIndex++;
							}						
						}						
					}			
				}
				else if(tolower(_contentBuff[Index.pivot + 2]) == 'f')
				{
					if(tolower(_contentBuff[Index.pivot + 3]) == 'r')
					{
						if(tolower(_contentBuff[Index.pivot + 4]) == 'a')
						{
							if(tolower(_contentBuff[Index.pivot + 5]) == 'm')
							{
								if(tolower(_contentBuff[Index.pivot + 6]) == 'e')
								{
									if(_contentBuff[Index.pivot + 7] == '=')
									{
										Index.firstShiftIndex = 8;
										while(Index.firstShiftIndex < _buffSize)
										{
											if(tolower(_contentBuff[Index.pivot + Index.firstShiftIndex]) == 's')
											{
												if(tolower(_contentBuff[Index.pivot + Index.firstShiftIndex + 1]) == 'r')
												{
													if(tolower(_contentBuff[Index.pivot + Index.firstShiftIndex + 2]) == 'c')
													{
														if(_contentBuff[Index.pivot + Index.firstShiftIndex + 3] == '=')
														{
															if(_contentBuff[Index.pivot + Index.firstShiftIndex + 4] == '\"')
															{
																Index.secondShiftIndex = 5;
																while(_contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex] != '\"' && Index.tarIndex < 1024)
																{
																	//CacheOfURL[Index.tarIndex] = _contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex];
																	memcpy(&CacheOfURL[Index.tarIndex], &_contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex], 1);
																	Index.secondShiftIndex++;
																	Index.tarIndex++;
																}
															}
															else if(_contentBuff[Index.pivot + Index.firstShiftIndex + 4] == '\'')
															{
																Index.secondShiftIndex = 5;
																while(_contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex] != '\'' && Index.tarIndex < 1024)
																{
																	//CacheOfURL[Index.tarIndex] = _contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex];
																	memcpy(&CacheOfURL[Index.tarIndex], &_contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex], 1);
																	Index.secondShiftIndex++;
																	Index.tarIndex++;
																}
															}
															else
															{
																Index.secondShiftIndex = 4;
																while(_contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex] != '>' && Index.tarIndex < 1024)
																{
																	//CacheOfURL[Index.tarIndex] = _contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex];
																	memcpy(&CacheOfURL[Index.tarIndex], &_contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex], 1);
																	Index.secondShiftIndex++;
																	Index.tarIndex++;
																}
															}
															//CacheOfURL[Index.tarIndex + 1] = '\0';
															memcpy(&CacheOfURL[Index.tarIndex], "\0", 1);
															Index.tarIndex++;
															CombinationWithBaseURL(_baseURL, CacheOfURL);
															CombinationTags(_file, CacheOfURL, 'r');
															break;
														}
													}
												}
											}
											Index.firstShiftIndex++;
										}
									}					
								}					
							}
						}				
					}						
				}
			}
			
			//Begin spliting <link href=> tags//
			if(tolower(_contentBuff[Index.pivot + 1]) == 'l')
			{
				if(tolower(_contentBuff[Index.pivot + 2]) == 'i')
				{
					if(tolower(_contentBuff[Index.pivot + 3]) == 'n')
					{
						if(tolower(_contentBuff[Index.pivot + 4]) == 'k')
						{
							Index.firstShiftIndex = 5;
							while(Index.firstShiftIndex < _buffSize)
							{
								if(tolower(_contentBuff[Index.pivot + Index.firstShiftIndex]) == 'h')
								{
									if(tolower(_contentBuff[Index.pivot + Index.firstShiftIndex + 1]) == 'r')
									{
										if(tolower(_contentBuff[Index.pivot + Index.firstShiftIndex + 2]) == 'e')
										{
											if(tolower(_contentBuff[Index.pivot + Index.firstShiftIndex + 3]) == 'f')
											{
												if(_contentBuff[Index.pivot + Index.firstShiftIndex + 4] == '=')
												{
													if(_contentBuff[Index.pivot + Index.firstShiftIndex + 5] == '\"')
													{
														Index.secondShiftIndex = 6;
														while(_contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex] != '\"' && Index.tarIndex < 1024)
														{
															//CacheOfURL[Index.tarIndex] = _contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex];
															memcpy(&CacheOfURL[Index.tarIndex], &_contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex], 1);
															Index.secondShiftIndex++;
															Index.tarIndex++;
														}
													}
													else if(_contentBuff[Index.pivot + Index.firstShiftIndex + 5] == '\'')
													{
														Index.secondShiftIndex = 6;
														while(_contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex] != '\'' && Index.tarIndex < 1024)
														{
															//CacheOfURL[Index.tarIndex] = _contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex];
															memcpy(&CacheOfURL[Index.tarIndex], &_contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex], 1);
															Index.secondShiftIndex++;
															Index.tarIndex++;
														}
													}
													else
													{
														Index.secondShiftIndex = 5;
														while(_contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex] != '>' || _contentBuff[Index.pivot + Index.firstShiftIndex + Index.firstShiftIndex] != ' ' && Index.tarIndex < 1024)
														{
															//CacheOfURL[Index.tarIndex] = _contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex];
															memcpy(&CacheOfURL[Index.tarIndex], &_contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex], 1);
															Index.secondShiftIndex++;
															Index.tarIndex++;
														}										
													}
													//CacheOfURL[Index.tarIndex + 1] = '\0';
													memcpy(&CacheOfURL[Index.tarIndex], "\0", 1);								
													Index.tarIndex++;					
													CombinationWithBaseURL(_baseURL, CacheOfURL);
													CombinationTags(_file, CacheOfURL, 'l');
													break;
												}
											}
										}
									}
								}
								Index.firstShiftIndex++;
							}
						}
					}
				}
			}
			
			//Begin spliting <form action=> tags//
			if(tolower(_contentBuff[Index.pivot + 1]) == 'f')
			{
				if(tolower(_contentBuff[Index.pivot + 2]) == 'o')
				{
					if(tolower(_contentBuff[Index.pivot + 3]) == 'r')
					{
						if(tolower(_contentBuff[Index.pivot + 4]) == 'm')
						{
							Index.firstShiftIndex = 5;
							while(Index.firstShiftIndex < _buffSize)
							{
								if(tolower(_contentBuff[Index.pivot + Index.firstShiftIndex]) == 'a')
								{
									if(tolower(_contentBuff[Index.pivot + Index.firstShiftIndex + 1]) == 'c')
									{
										if(tolower(_contentBuff[Index.pivot + Index.firstShiftIndex + 2]) == 't')
										{
											if(tolower(_contentBuff[Index.pivot + Index.firstShiftIndex + 3]) == 'i')
											{
												if(tolower(_contentBuff[Index.pivot + Index.firstShiftIndex + 4]) == 'o')
												{
													if(tolower(_contentBuff[Index.pivot + Index.firstShiftIndex + 5]) == 'n')
													{
														if(_contentBuff[Index.pivot + Index.firstShiftIndex + 6] == '=')
														{														
															if(_contentBuff[Index.pivot + Index.firstShiftIndex + 7] == '\"')
															{
																Index.secondShiftIndex = 8;
																while(_contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex] != '\"' && Index.tarIndex < 1024 )
																{
																	//CacheOfURL[Index.tarIndex] = _contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex];
																	memcpy(&CacheOfURL[Index.tarIndex], &_contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex], 1);
																	Index.secondShiftIndex++;
																	Index.tarIndex++;
																}
															}
															else if(_contentBuff[Index.pivot + Index.firstShiftIndex + 7] == '\'')
															{
																Index.secondShiftIndex = 8;
																while(_contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex] != '\'' && Index.tarIndex < 1024)
																{
																	//CacheOfURL[Index.tarIndex] = _contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex];
																	memcpy(&CacheOfURL[Index.tarIndex], &_contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex], 1);
																	Index.secondShiftIndex++;
																	Index.tarIndex++;
																}
															}
															else
															{
																Index.secondShiftIndex = 7;
																while(_contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex] != '>' && Index.tarIndex < 1024)
																{
																	//CacheOfURL[Index.tarIndex] = _contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex];
																	memcpy(&CacheOfURL[Index.tarIndex], &_contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex], 1);
																	Index.secondShiftIndex++;
																	Index.tarIndex++;
																}
															}
															//CacheOfURL[Index.tarIndex + 1] = '\0';
															memcpy(&CacheOfURL[Index.tarIndex], "\0", 1);
															Index.tarIndex++;
															CombinationWithBaseURL(_baseURL, CacheOfURL);
															CombinationTags(_file, CacheOfURL, 'f');
															break;
														}
													}
												}	
											}	
										}																		
									}								
								}
								Index.firstShiftIndex++;
							}
						}
					}
				}
			}
			*/
			
			//Begin spliting <a href=> tags//
			if(tolower(_contentBuff[Index.pivot + 1]) == 'a')
			{			
				Index.firstShiftIndex = 2;
				while(Index.firstShiftIndex < _buffSize)
				{
					if(tolower(_contentBuff[Index.pivot + Index.firstShiftIndex]) == 'h')
					{
						if(tolower(_contentBuff[Index.pivot + Index.firstShiftIndex + 1]) == 'r')
						{
							if(tolower(_contentBuff[Index.pivot + Index.firstShiftIndex + 2]) == 'e')
							{
								if(tolower(_contentBuff[Index.pivot + Index.firstShiftIndex + 3]) == 'f')
								{
									if(_contentBuff[Index.pivot + Index.firstShiftIndex + 4] == '=')
									{
										if(_contentBuff[Index.pivot + Index.firstShiftIndex + 5] == '\"')
										{
											Index.secondShiftIndex = 6;
											while(_contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex] != '\"' && Index.tarIndex < 1024)
											{
												//CacheOfURL[Index.tarIndex] = _contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex];	
												memcpy(&CacheOfURL[Index.tarIndex], &_contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex], 1);
												Index.secondShiftIndex++;
												Index.tarIndex++;												
											}
										}
										else if(_contentBuff[Index.pivot + Index.firstShiftIndex + 5] == '\'')
										{
											Index.secondShiftIndex = 6;
											while(_contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex] != '\'' && Index.tarIndex < 1024)
											{
												//CacheOfURL[Index.tarIndex] = _contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex];
												memcpy(&CacheOfURL[Index.tarIndex], &_contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex], 1);
												Index.secondShiftIndex++;
												Index.tarIndex++;
											}
										}
										else
										{
											Index.secondShiftIndex = 5;
											while(_contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex] != '>' && Index.tarIndex < 1024)
											{
												//CacheOfURL[Index.tarIndex] = _contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex];
												memcpy(&CacheOfURL[Index.tarIndex], &_contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex], 1);
												Index.secondShiftIndex++;
												Index.tarIndex++;
											}
										}
										//CacheOfURL[Index.tarIndex + 1] = '\0';						
										memcpy(&CacheOfURL[Index.tarIndex], "\0", 1);
										Index.tarIndex++;
										CombinationWithBaseURL(_baseURL, CacheOfURL);
										CombinationTags(_file, CacheOfURL, 'a');
										break;
									}
								}
							}
						}
					}
					Index.firstShiftIndex++;
				}
			}
			
		}
		Index.pivot++;
	}
	
	return 1;
}

int FindBaseURL(char *_src, char *_tar, int _curURLNum)
{
	int eleCount = 0;
	int pivot = 0;
	int arrow = 0;
	
	char tmpStr[1024];
	tmpStr[1024] = '\0';
	
	while(true)
	{
		if(_src[pivot] == '\0')
		{
			if(eleCount == _curURLNum)
			{
				memcpy(&tmpStr[arrow], "\0", 1);
				memcpy(_tar, tmpStr, strlen(tmpStr) + 1);
				return 1;
			}
			else
			{
				eleCount++;
				arrow = 0;
				pivot++;
			}
		}
		else
		{
			memcpy(&tmpStr[arrow], &_src[pivot], 1);
			arrow++;
			pivot++;
		}
	}
	
	return 1;
} 

int readContent(FInfo *_file, char *_offsetBuff)
{
	int begOffset = 0;
	int endOffset = 0;
	int size = 0;
	int key = 0;
	int resul = 0;
	int urlCount = 0;
	
	char *contentBuff;
	char *baseURLBuff;
	char *pch;
	char tmpTitleTag[7];
	char tmpEndTag[8];
	char baseURL[128];
	
	strcpy(tmpTitleTag, "<LINK>");
	strcpy(tmpEndTag, "</LINK>");

	tmpTitleTag[7] = '\0';
	tmpEndTag[8] = '\0';
	
	baseURLBuff = (char*)malloc(sizeof(char) * (128 * 1024 * 1024));
	if(baseURLBuff == NULL) {fputs ("Memory error (BaseURL BUFF)\n", stderr); exit (2);}
		
	bzero(&baseURL, sizeof(baseURL));
	baseURLEx(_file->Header, baseURLBuff);
					
  pch = strtok(_offsetBuff, "\n");
  
  while(pch != NULL)
  {
		if(key % 2 != 0)
		{
			endOffset = atoi(pch);
			
			if(key > 0)
			{	
    		size = endOffset - begOffset;
    		
    		cout << "=================================" << endl;
    		cout << "OFFSET : " << begOffset << "\t" << endOffset << "\t" << size << endl;
    		
    		contentBuff = (char*)malloc(sizeof(char) * size);
				if(contentBuff == NULL) {fputs ("Memory error (Content BUFF)\n", stderr); exit (2);}
						
    		
    		fseek(_file->Content, begOffset, SEEK_SET);
    		resul = fread(contentBuff, 1, size, _file->Content);

    		cout << resul << "\t" << size << "\t[" << ftell(_file->Content) << "]" << endl;
    		cout << "=================================\n" << endl;
    		
    		if(resul != size) {fputs ("Reading error (Content BUFF)\n", stderr);break;}
    		
 				if(size != 0)
 				{	
					FindBaseURL(baseURLBuff, baseURL, urlCount);
					urlCount++;
					
					fwrite(tmpTitleTag, 1, strlen(tmpTitleTag), _file->ExLinks);
					
					cout << "Start extracting links...\n";
					
					LinksExtracting(_file->ExLinks, contentBuff, baseURL, resul);
	    		
	    		cout << "Finish extracting links!\n";
	    		fwrite(tmpEndTag, 1, strlen(tmpEndTag), _file->ExLinks);
				
				}
    		free(contentBuff);
    	}
		}
		else
		{
			begOffset = atoi(pch);
		}
		
    pch = strtok(NULL, "\n");
    key++;
  }
  free(baseURLBuff);
	return 1;
}


int extractHeaderData(FInfo *_file)
{
	char *OffsetBuff;
	int buffSize = 256 * 1024 * 1024;			//256MB
	OffsetBuff = (char*)malloc(sizeof(char) * buffSize);
	
	string xmlTileStr = "<?xml version='1.0' encoding='utf-8'?><EXLINKS>";
	string xmlEndTag = "</EXLINKS>\0";
		
	XMLParser(_file, OffsetBuff);
	rewind(_file->Header);
	
	fwrite(xmlTileStr.c_str(), 1, xmlTileStr.length(), _file->ExLinks);	
	readContent(_file, OffsetBuff);
	fputs(xmlEndTag.c_str(), _file->ExLinks);
	
	free(OffsetBuff);
	return 1;
}
