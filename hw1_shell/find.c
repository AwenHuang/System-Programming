#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <ctype.h>
#define MAX 1024

void find(FILE *fp,char key[],char path[]);
int comd_c = 0;
int main(int argc,char *argv[])
{
		DIR *dp;
		struct dirent *dirp;
		FILE *fp;
		char buf[MAX],pathname[100];
		int comd_r=0;

		if(argc == 4) 
		{
				if(strcmp(argv[1],"-c") == 0)
						comd_c = 1;
				else if(strcmp(argv[1],"-r") == 0)
						comd_r = 1;
				else if(strcmp(argv[1],"-cr") == 0 || strcmp(argv[1],"-rc") == 0)
				{
						comd_c = 1;
						comd_r = 1;
				}
		}
		else if(argc == 5)
		{
				if(strcmp(argv[1],"-c") == 0 || strcmp(argv[2],"-c") == 0)
						comd_c = 1;
				else if(strcmp(argv[1],"-r") == 0 || strcmp(argv[2],"-r") == 0)
						comd_r = 1;
		}

		if(comd_r == 1) // target is directory
		{
				dp = opendir(argv[argc-1]);
				while((dirp = readdir(dp))!=NULL)
				{
						
						
						sprintf(pathname,"%s%s",argv[argc-1],dirp->d_name);
						fp = fopen(pathname,"r"); 
						find(fp,argv[argc-2],pathname);
						
				}
		}
		else if(comd_r == 0) // target is file
		{
				fp = fopen(argv[argc-1],"r");
				find(fp,argv[argc-2],argv[argc-1]);
		}


		return 0;
}

void find(FILE *fp,char key[],char path[])
{
		char buf[MAX];
		char *ptr;
		int line_num,pos,key_len;

		line_num = 1;
		key_len = strlen(key);

		while(fgets(buf,MAX,fp)!=NULL) // 從開啟的檔案一行一行讀取資料
		{
				ptr = buf; // 這樣才會繼續抓

				if(comd_c == 1)//要分大小寫
				{
						while((ptr = strstr(ptr,key))!=NULL) 
						{
								pos = (strlen(buf)-strlen(ptr))+1;
								printf("In %s Line %d : Char %d~%d\n",path,line_num,pos,pos+key_len-1);
								ptr++;
						}
						line_num++;
				}
				else if(comd_c == 0)//不分大小寫
				{
						while((ptr = strcasestr(ptr,key))!=NULL)
						{
								pos = (strlen(buf)-strlen(ptr))+1;
								printf("In %s Line %d : Char %d~%d\n",path,line_num,pos,pos+key_len-1);
								ptr++;
						}
						line_num++;
				}

				
		}
}

		
	



