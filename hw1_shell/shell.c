#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <unistd.h>
#define MAXSIZE 1024

int main(void)
{
		pid_t pid;
		int status;
		int num;
		char *argument[10] = {NULL}; // 儲存參數
		char buf[MAXSIZE]; // 儲存command line
		char *ptr;
	
		printf("## "); // ## 後面輸入commandline

		while(fgets(buf,MAXSIZE,stdin) != NULL)
		{
				num = 0;
				// 切割command line , 將參數逐一儲存到*argv[]
				ptr = strtok(buf," \n\t");
				while(ptr != NULL)
				{
						if(argument[num] != NULL)
								free(argument[num]);
						
						argument[num] = (char *)malloc(sizeof(char)*strlen(ptr));
						strcpy(argument[num],ptr);
						num++;
						ptr = strtok(NULL," \n\t");
				}
				argument[num] = NULL;
				
				if(strcmp(argument[0],"exit")==0)
						break;
				if(strcmp(argument[0],"cd") == 0)
				{
						if(chdir(argument[1])!=0)
								 printf("%s: No this file or directory.\n",argument[1]);
				}
				else
				{
						if((pid=fork()) < 0) //fork error
								printf("fork error!\n");

						else if(pid == 0) //child
						{
								if(strcmp(argument[0],"find") == 0) //use find command
										execvp("./find",argument); // execvp() 會在目錄查找./find文件名,找到後執行該文件,然後將第二個參數(指標陣列型態)傳給執行的文件
						//執行成功的話函數不返回，若失敗則返回-1
								else if(strcmp(argument[0],"rename") == 0)
										execvp("./rename",argument);
								else 
										execvp(argument[0],argument);

								printf("couldn't excute: %s\n",buf);
								exit(127);
						}
				}
				// parent 
				if((pid=waitpid(pid,&status,0)) < 0)
						printf("waitpid error\n");
				printf("## ");
		}
		return 0;
}





	
