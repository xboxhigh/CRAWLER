


int LinksExtracting(FInfo *_file, char *_contentBuff, char *_baseURL)
{
	int buffSize = strlen(_contentBuff);
	
	IndexNums Index;
	char CacheOfURL[1024];
	
	Index.firstShiftIndex = 0;
	Index.secondShiftIndex = 0;
	Index.tarIndex = 0;
	Index.pivot = 0;
	
	//Check Base URL Link//
	CheckBaseLinks(_contentBuff, _baseURL);
	
	//Check orther tags//
	while(Index.pivot < buffSize)
	{
		Index.firstShiftIndex = 0;
		Index.secondShiftIndex = 0;
		bzero(&tmpURLBuff, sizeof(tmpURLBuff));
			
		if(_contentBuff[Index.pivot] == '<')
		{
			//Begin spliting <img src> tags & <iframe src>tags//	
			if(tolower(_contentBuff[Index.pivot + 1]) == 'i')
			{
				if(tolower(_contentBuff[Index.pivot + 2]) == 'm')
				{
					if(tolower(_contentBuff[Index.pivot + 3]) == 'g')
					{
						if(_contentBuff[Index.pivot + 4] == '=')
						{
							Index.firstShiftIndex += 5;
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
												Index.secondShiftIndex += 5;
												while(_contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex] != '\"')
												{
													CacheOfURL[Index.tarIndex] = _contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex];
													Index.secondShiftIndex++;
													Index.tarIndex++;
												}
											}
											else if(_contentBuff[Index.pivot + Index.firstShiftIndex + 4] == '\'')
											{
												Index.secondShiftIndex += 5;
												while(_contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex] != '\'')
												{
													CacheOfURL[Index.tarIndex] = _contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex];
													Index.secondShiftIndex++;
													Index.tarIndex++;
												}
											}
											else
											{
												Index.secondShiftIndex += 5;
												while(_contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex] != '>')
												{
													CacheOfURL[Index.tarIndex] = _contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex];
													Index.secondShiftIndex++;
													Index.tarIndex++;
												}
											}
											CacheOfURL[Index.tarIndex + 1] = '\0';
											Index.pivot += Index.firstShiftIndex + Index.secondShiftIndex;
														
											CombinationWithBaseURL(_baseURL, CacheOfURL);
											CombinationTags(_file->ExLinks, CacheOfURL, 'a');
										}
									}
								}
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
										Index.firstShiftIndex += 8;
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
															Index.secondShiftIndex += 5;
															while(_contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex] != '\"')
															{
																CacheOfURL[Index.tarIndex] = _contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex];
																Index.secondShiftIndex++;
																Index.tarIndex++;
															}
														}
														else if(_contentBuff[Index.pivot + Index.firstShiftIndex + 4] == '\'')
														{
															Index.secondShiftIndex += 5;
															while(_contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex] != '\'')
															{
																CacheOfURL[Index.tarIndex] = _contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex];
																Index.secondShiftIndex++;
																Index.tarIndex++;
															}
														}
														else
														{
															Index.secondShiftIndex += 5;
															while(_contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex] != '>')
															{
																CacheOfURL[Index.tarIndex] = _contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex];
																Index.secondShiftIndex++;
																Index.tarIndex++;
															}
														}
														CacheOfURL[Index.tarIndex + 1] = '\0';
														Index.pivot += Index.firstShiftIndex + Index.secondShiftIndex;
																	
														CombinationWithBaseURL(_baseURL, CacheOfURL);
														CombinationTags(_file->ExLinks, CacheOfURL, 'a');
													}
												}
											}
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
							Index.firstShiftIndex += 5;
							
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
												if(_contentBuff[Index.pivot + Index.firstShiftIndex + 5]) == '\"')
												{
													Index.secondShiftIndex = Index.firstShiftIndex + 6;
													while(_contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex] != '\"')
													{
														CacheOfURL[Index.tarIndex] = _contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex];
														Index.secondShiftIndex++;
														Index.tarIndex++;
													}
												}
												else if(_contentBuff[Index.pivot + Index.firstShiftIndex + 5]) == '\'')
												{
													Index.secondShiftIndex = Index.firstShiftIndex + 6;
													while(_contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex] != '\'')
													{
														CacheOfURL[Index.tarIndex] = _contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex];
														Index.secondShiftIndex++;
														Index.tarIndex++;
													}
												}
												else
												{
													Index.secondShiftIndex = Index.firstShiftIndex + 5;
													while(_contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex] != '>' || _contentBuff[Index.pivot + Index.firstShiftIndex + Index.firstShiftIndex] != ' ')
													{
														CacheOfURL[Index.tarIndex] = _contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex];
														Index.secondShiftIndex++;
														Index.tarIndex++;
													}										
												}
												CacheOfURL[Index.tarIndex + 1] = '\0';
												Index.pivot += Index.firstShiftIndex + Index.secondShiftIndex;
												
												CombinationWithBaseURL(_baseURL, CacheOfURL);
												CombinationTags(_file->ExLinks, CacheOfURL, 'a');
											}
										}
									}
								}
							}			
						}
					}
				}
				
				
				
				
				
				CmpStr.fourChr[0] = tolower(_contentBuff[Index.pivot + 1]);
				CmpStr.fourChr[1] = tolower(_contentBuff[Index.pivot + 2]);
				CmpStr.fourChr[2] = tolower(_contentBuff[Index.pivot + 3]);
				CmpStr.fourChr[3] = tolower(_contentBuff[Index.pivot + 4]);
				CmpStr.fourChr[4] = '\0';
				
				if(strcmp(CmpStr.fourChr, "link") == 0)
				{
					Index.pivot += 5;
					
					while(_contentBuff[Index.pivot + Index.firstShiftIndex] != '>' && (Index.pivot + Index.firstShiftIndex) < buffSize)
					{
						CmpStr.fiveChr[0] = tolower(_contentBuff[Index.pivot + Index.firstShiftIndex + 1]);
						CmpStr.fiveChr[1] = tolower(_contentBuff[Index.pivot + Index.firstShiftIndex + 2]);
						CmpStr.fiveChr[2] = tolower(_contentBuff[Index.pivot + Index.firstShiftIndex + 3]);
						CmpStr.fiveChr[3] = tolower(_contentBuff[Index.pivot + Index.firstShiftIndex + 4]);
						CmpStr.fiveChr[4] = tolower(_contentBuff[Index.pivot + Index.firstShiftIndex + 5]);
						CmpStr.fiveChr[5] = '\0';
						
						if(strcmp(CmpStr.fiveChr, "href=") == 0)
						{
							Index.secondShiftIndex += 6;
							
							checkTypePerLink(Index, _contentBuff, tmpURLBuff);
							combinationWithBaseURL(baseURL, tmpURLBuff);
							combinationTags(_file, tmpURLBuff, 'l');
						}
						Index.firstShiftIndex++;
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
							Index.firstShiftIndex += 5;
							
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
															Index.secondShiftIndex += 8;
															while(_contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex] != '\"')
															{
																CacheOfURL[Index.tarIndex] = _contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex];
																Index.secondShiftIndex++;
																Index.tarIndex++;
															}
														}
														else if(_contentBuff[Index.pivot + Index.firstShiftIndex + 7] == '\'')
														{
															Index.secondShiftIndex += 8;
															while(_contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex] != '\'')
															{
																CacheOfURL[Index.tarIndex] = _contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex];
																Index.secondShiftIndex++;
																Index.tarIndex++;
															}
														}
														else
														{
															Index.secondShiftIndex += 7;
															while(_contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex] != '>')
															{
																CacheOfURL[Index.tarIndex] = _contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex];
																Index.secondShiftIndex++;
																Index.tarIndex++;
															}
														}
														CacheOfURL[Index.tarIndex + 1] = '\0';
														Index.pivot += Index.firstShiftIndex + Index.secondShiftIndex;
														
														CombinationWithBaseURL(_baseURL, CacheOfURL);
														CombinationTags(_file->ExLinks, CacheOfURL, 'a');
													}
												}
											}	
										}	
									}																		
								}								
							}
						}
					}
				}
			}			
			//Begin spliting <a href=> tags//
			if(tolower(_contentBuff[Index.pivot + 1]) == 'a')
			{
				Index.firstShiftIndex += 2;
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
									if(_contentBuff[Index.pivot + Index.firstShiftIndex + 5]) == '\"')
									{
										Index.secondShiftIndex = Index.firstShiftIndex + 6;
										while(_contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex] != '\"')
										{
											CacheOfURL[Index.tarIndex] = _contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex];
											Index.secondShiftIndex++;
											Index.tarIndex++;
										}
									}
									else if(_contentBuff[Index.pivot + Index.firstShiftIndex + 5]) == '\'')
									{
										Index.secondShiftIndex = Index.firstShiftIndex + 6;
										while(_contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex] != '\'')
										{
											CacheOfURL[Index.tarIndex] = _contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex];
											Index.secondShiftIndex++;
											Index.tarIndex++;
										}
									}
									else
									{
										Index.secondShiftIndex = Index.firstShiftIndex + 5;
										while(_contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex] != '>' || _contentBuff[Index.pivot + Index.firstShiftIndex + Index.firstShiftIndex] != ' ')
										{
											CacheOfURL[Index.tarIndex] = _contentBuff[Index.pivot + Index.firstShiftIndex + Index.secondShiftIndex];
											Index.secondShiftIndex++;
											Index.tarIndex++;
										}										
									}
									CacheOfURL[Index.tarIndex + 1] = '\0';
									Index.pivot += Index.firstShiftIndex + Index.secondShiftIndex;
									
									CombinationWithBaseURL(_baseURL, CacheOfURL);
									CombinationTags(_file->ExLinks, CacheOfURL, 'a');
								}
							}
						}
					}
				}				
			}
			
			//Index.pivot += strlen(CacheOfURL);
		}
		Index.pivot++;
	}
	
	return 1;
}
