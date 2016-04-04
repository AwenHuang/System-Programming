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
		char *argument[10] = {NULL}; // �x�s�Ѽ�
		char buf[MAXSIZE]; // �x�scommand line
		char *ptr;
	
		printf("## "); // ## �᭱��Jcommandline

		while(fgets(buf,MAXSIZE,stdin) != NULL)
		{
				num = 0;
				// ����command line , �N�ѼƳv�@�x�s��*argv[]
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
										execvp("./find",argument); // execvp() �|�b�ؿ��d��./find���W,�������Ӥ��,�M��N�ĤG�ӰѼ�(���а}�C���A)�ǵ����檺���
						//���榨�\���ܨ�Ƥ���^�A�Y���ѫh��^-1
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





	
