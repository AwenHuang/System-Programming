#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 1024

void label(char input[]);
void Insert(char input[],int pos,int end);
void Newline(char input[],int pos);
void Proper(char input[],int start_pos,int end_pos);
void Upper(char input[],int start_pos,int end_pos);
void Lower(char input[],int start_pos,int end_pos);
void Reverse(char input[],int start_pos,int end_pos);
FILE *fp2;

int main(int argc,char *argv[])
{

		int i;
		char *pch,*result;
		char filename[20],input[MAX];
		FILE *fp;

		strcpy(filename,argv[1]);
		fp = fopen(filename,"r");

		// 創建.output文件
		pch = strstr(filename,".tex");
		strncpy(pch,".output",7);
		fp2 = fopen(filename,"a");

		if(!fp){
				printf("File not exit!\n");
				exit(1);
		}
		while(fgets(input,MAX,fp)!=NULL)
		{
				//input[strlen(input)-1] = '\0';
				label(input);
		}
		return 0;

}
void label(char input[])
{
		int i,pos1,pos2,mark_num=0,n=0;
		//int mark[6]={0}; // 記錄標籤出現的次數,Upper(0) Lower(1) Proper(2) Reverse(3) Newline(4) Insert(5)
		int order[100]={0}; // 記錄標籤出現順序
		char *test1,*test2;
		char *array_1[4] = {"<Upper>","<Lower>","<Proper>","<Reverse>"};
		char *array_2[4] = {"</Upper>","</Lower>","</Proper>","</Reverse>"};

		for(i=0;i<4;i++)
		{
				// 尋找是否有標籤字串
				if(strstr(input,array_1[i])!= NULL)
				{
						// 算出標籤在字串哪個位置
						pos1 = test1-input;
						pos2 = test2-input;
			
						if(i == 0) // 出現Upper標籤
						{
								order[n++] = 0;
							
						}
						else if(i == 1) // 出現Lower標籤
						{
								order[n++] = 1;
							
						}
						else if(i == 2) // 出現Proper標籤
						{
								order[n++] = 2;
							
						}
						else if(i == 3) // 出現Reverse標籤
						{
								order[n++] = 3;
								
						}
				}
		}
		if(strstr(input,"<Newline>")!=NULL) // 出現Newline標籤
		{
				order[n++] = 4;
		
		}
	
		if(strstr(input,"<Insert char = ")!=NULL) // 出現Insert標籤
		{
				order[n++] = 5;
			
		}

		// 計算mark[]陣列中的總合,如果>=1,則表示該字串出現標籤種類不只一種
		
	
		int order_len,tag;
		
		order_len = n;

		if(order_len >= 1) 
		{
				tag = order[order_len-1];
				if(tag >=0 && tag<=3)
				{
						
								// 分別記錄頭尾標籤的指標位置
								test1 = strstr(input,array_1[tag]);
								test2 = strstr(input,array_2[tag]);
								// 算出標籤在字串哪個位置
								pos1 = test1-input;
								pos2 = test2-input;

					
								if(tag == 0) // Upper
										Upper(input,pos1,pos2);
								else if(tag == 1) // Lower
										Lower(input,pos1,pos2);
								else if(tag == 2) // Proper
										Proper(input,pos1,pos2);
								else if(tag == 3) // Reverse
										Reverse(input,pos1,pos2);
				}										
				else if(tag == 4) // Newline
				{
						test1 = strstr(input,"<Newline>");
						pos1 = test1 - input;
						Newline(input,pos1);
				}
				else if(tag == 5) // Insert
				{
						test1 = strstr(input,"<Insert char = '");
						test2 = strstr(input,">");
						pos1 = test1 - input;
						pos2 = test2 - input;
						Insert(input,pos1,pos2);
				}
		}
		else
				fprintf(fp2,"%s",input);
		
	
}
void Insert(char input[],int pos,int end)
{
		int i=0,j=0,k,len,times,find=0,temp1,temp2,ch_len;
		char result[100]={0};
		char ch;
		char *pch;
		len = strlen("<Insert char = '");
		
		pch = strstr(input,"'");
		while(pch != NULL)
		{
				find++;
				//找到第三個"'"和第四個"'"時,分別記錄他們的位置
				if(find == 3)
						temp1 = pch-input;
				else if(find == 4)
						temp2 = pch-input;
				pch = strstr(pch+1,"'");
		}
		//記錄number是幾位數,並宣告剛好位數的字串
		ch_len = temp2-temp1;
		char temp[ch_len];

		while(input[i] != '\0')
		{
				if(i == pos)
				{
						i = i+len; // i會跑到所要的character
						ch = input[i];

						i = i+(temp1-i)+1; // i會跑到第三個"'",所以需要再加1才會是要的number
						
						//儲存number到字串中
						for(k=0;k<ch_len;k++)
								temp[k] = input[i++];

						times = atoi(temp);//轉換字串為int整數型態
						i = end+1;//end所代表的位置為">",故i必須再加1

						//將charater用for迴圈存入result中
						for(k=0;k<times;k++)
							result[j++] = ch;
				}
				result[j++] = input[i++]; 
		}
		fprintf(fp2,"%s",result);
}



void Newline(char input[],int pos)
{
		int i=0,j=0,len;
		char result[100]={0};

		len = strlen("<Newline>");
		while(input[i] != '\0')
		{
				if(i == pos)
				{
						i = (i+len)-1;
						input[i] = '\n';
				}
				result[j++] = input[i++];
		}
		fprintf(fp2,"%s",result);
}



void Proper(char input[],int start_pos,int end_pos)
{
		int i=0,j=0,len;
		char result[100]={0};

		len = strlen("<Proper>");
		while(input[i] != '\0')
		{
				if(i == start_pos) // i位置跑到<Proper>,略過
						i = i+len;
				else if(i == end_pos) // i位置跑到</Proper>,略過
						i = i+len+1;
                // 當i在<Proper>和</Proper>之間時
				if(i >= (start_pos+len) && i< end_pos)
				{
						if(i == (start_pos+len)) // <Proper>標籤後的第一個字轉大寫
								input[i] = toupper(input[i]);
						if(input[i] == ' ') 
								input[i+1] = toupper(input[i+1]); // 空白後第一個字轉大寫
				}
				result[j++] = input[i++];
		}
		fprintf(fp2,"%s",result);


}

void Upper(char input[],int start_pos,int end_pos)
{
		int i=0,j=0,len;
		char result[100]={0}; //字串歸零
		
		len = strlen("<Upper>");		
		while(input[i] != '\0')
		{
				if(i == start_pos) // i位置跑到<Upper>,略過
						i = i+len;
				else if(i == end_pos) // i位置跑到</Upper>,略過
						i = i+len+1;
				// 當i在<Upper>和</Upper>之間時,input[i]做toupper
				if(i >= (start_pos+len) && i< end_pos)
						input[i] = toupper(input[i]);
				result[j++] = input[i++];
		}
		
		fprintf(fp2,"%s",result);
}
void Lower(char input[],int start_pos,int end_pos)
{
		int i=0,j=0,len;
 		char result[100]={0};//字串歸零
		
		len = strlen("<Lower>");
		while(input[i] != '\0')
		{
				if(i == start_pos) // i位置跑到<Lower>,略過
						i = i+len;
				else if(i == end_pos) // i位置跑到</Lower>,略過
						i = i+len+1;
				// 當i在<Lower>和</Lower>之間時,input[i]做tolower
				if(i >= (start_pos+len) && i< end_pos)
						input[i] = tolower(input[i]);
						
								
				result[j++] = input[i++];
		}
		fprintf(fp2,"%s",result);
}
void Reverse(char input[],int start_pos,int end_pos)
{
		int i=0,j=0,k,n,m=0,len,reverse_len;
		char result[100]={0};
		
		len = strlen("<Reverse>");

		reverse_len = end_pos - (start_pos+len); // 要反轉的字串長度
		char temp[reverse_len];

		while(input[i] != '\0')
		{
				if(i == start_pos)
						i = i+len;
				else if(i == end_pos)
						i = i+len+1;

				//先把要反轉的字串反著儲存在temp[]
				if(i == (start_pos+len))
				{
						n=i; // 為了讓跑字串位置的i,在這保持不變
						for(k=reverse_len-1;k>=0;k--)
								temp[k] = input[n++];
				}
				
				if(i >= (start_pos+len) && i < end_pos) //會進這個迴圈 字串長度 次 EX:要reverse的字串長度為4,進入此迴圈次數則為4
						input[i] = temp[m++];
				
				result[j++] = input[i++];
		}

		fprintf(fp2,"%s",result);
}
				
















