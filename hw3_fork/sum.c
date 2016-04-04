#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/time.h>

void sum_fun(FILE *ptr,int degree,int avg,int time);

int main(int argc,char *argv[])
{
		FILE *fptr=NULL,*wptr=NULL;
		int i,degree = 1,avg = 0,time = 0;
		char c;
		for(i=0;i<argc;i++)
		{
				if(argv[i][0] == '-')
				{
						if(argv[i][1] == 'd') degree = atoi(argv[++i]);
						else if(argv[i][1] == 'f') fptr = fopen(argv[++i],"r"); 
						else if(argv[i][1] == 'o')	wptr = fopen(argv[++i],"w");
						else if(argv[i][1] == 'a') avg = 1;
						else if(argv[i][1] == 't') time = 1;
				}
		}
		printf("fptr = %d\n",fptr);
		sum_fun(fptr,degree,avg,time);
		return 0;
}

void sum_fun(FILE *fptr,int degree,int avg,int time)
{
		const int MAX = 10000;
		int number[MAX];
		int temp;
		int i,cont =0;
		int pipe(int pd[2]);
		pid_t pid[MAX];
		if(fptr != NULL){
				printf("file exist\n");
				while(fscanf(fptr,"%d",&temp)!=EOF) 
						number[cont++] = temp;
		}
		else 				
				while(scanf("%d",number[cont]) != EOF) cont++;
		for(i=0;i<cont;i++) printf("%d\n",number[i]);
}
