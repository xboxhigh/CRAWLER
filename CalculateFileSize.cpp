#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "globalFunc.h"

using namespace std;

#define LENGTH  256

/* just if is a directory*/
static int IsDir (char *name);
/* search target file, arg1 is current path, arg2 is target  file*/
static void search_file (char * path, int hour);

static int search_flag = 0;

/*just if is a directory*/
static int IsDir (char *name) 
{
	struct  stat  buff;  
	
	if (lstat(name,&buff)<0)
	return 0; //if not exist name ,ignore
	
	/*if is directory return 1 ,else return 0*/ 
	return S_ISDIR(buff.st_mode);
}


/*search  target file*/
static void search_file (char *path, int hour) 
{
	DIR	*directory;
	struct	dirent * dir_entry;
	char	buffer[LENGTH];
	int singleFileSize = 0, sum = 0;
	
	if((directory = opendir(path)) == NULL) 
	{
		fprintf(stderr, "%s", path);
		perror(" ");
		return;
	}
	
	while(dir_entry = readdir(directory)) 
	{
		if(!strcmp(dir_entry->d_name, ".") || !strcmp(dir_entry->d_name,"..")) 
		{
			/*  do	nothing*/
		}
		else
		{
			/* if is  boot  directory  add  "/" */
			if ((strcmp(path, "/")) == 0)
				sprintf(buffer, "%s%s", path, dir_entry->d_name);
			/*  if is not  boot  directory do not add "/"*/
			else
				sprintf(buffer, "%s/%s", path, dir_entry->d_name);
			
			printf("Now file : %s\n", buffer);
			
			FILE * pFile;
		  pFile = fopen (buffer, "r");
		  
		  if(pFile != NULL)
		  {
		  	fseek(pFile, 0, SEEK_END);
		  	singleFileSize = ftell(pFile);		  	
		    sum = sum + singleFileSize;
		    fclose (pFile);
		  }
		  else
		  	cout << "Not found such file, " << buffer << endl;
			
			
			/*
			if (IsDir(buffer))
				search_file (buffer, name);
			else 
			{
				if (strcmp(dir_entry->d_name,name)==0)
				{
					printf("%s\n", buffer);
					search_flag = 1;
				}
			}
			*/
		}
	}
	closedir(directory);
	
	FILE *recordPerHour;
	
	recordPerHour = fopen("FileSizeRecord.Log", "a+");
	
	fputs("Hour ", recordPerHour);
	fputs(itoa(hour).c_str(), recordPerHour);
	fputs(" : ", recordPerHour);
	fputs(itoa(sum).c_str(), recordPerHour);
	fputs("\n", recordPerHour);
	
	fclose(recordPerHour);
}


int main(int argc, char *argv[])
{
	static char *current_dir;
	static char *filename; 
	int hour = 0;
	
	time_t begTime;
	time_t endTime;
	time_t reslTime;
	
	time(&begTime);
	
	FILE *crawlPage;
	
	char dir[39];
	dir[39] = '\0';
	
	strcpy(dir, "/data2/xboxhigh/_gatheringFiles/bFile");
	
	/*
	if (argc == 1) 
	{
		printf("A few parameters!!\n");
		return 0;
	}
	
	
	if (argc == 2) 
	{
		current_dir = (char*)getcwd(current_dir, LENGTH);
		filename = argv[1];
	}	

	if (argc == 3) 
	{
		length = strlen(argv[1]);
	
		if (length > 1 && (argv[1][length - 1] == '/')) 
		{
			argv[1][length-1] = '\0';
			//printf("%d\n",strlen(argv[1]));
		}		
		current_dir = argv[1];
		filename = argv[2];
	}
	*/
	
	
	while(1)
	{
		time(&endTime);
		reslTime = endTime - begTime;
		
		if(reslTime % 3600 == 0)
		{			
			search_file(dir, hour);
			hour++;
		}
		
	}
	
	
	
	return 0;
}
