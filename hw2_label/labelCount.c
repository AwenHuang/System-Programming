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

		// �Ы�.output���
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
		//int mark[6]={0}; // �O�����ҥX�{������,Upper(0) Lower(1) Proper(2) Reverse(3) Newline(4) Insert(5)
		int order[100]={0}; // �O�����ҥX�{����
		char *test1,*test2;
		char *array_1[4] = {"<Upper>","<Lower>","<Proper>","<Reverse>"};
		char *array_2[4] = {"</Upper>","</Lower>","</Proper>","</Reverse>"};

		for(i=0;i<4;i++)
		{
				// �M��O�_�����Ҧr��
				if(strstr(input,array_1[i])!= NULL)
				{
						// ��X���Ҧb�r����Ӧ�m
						pos1 = test1-input;
						pos2 = test2-input;
			
						if(i == 0) // �X�{Upper����
						{
								order[n++] = 0;
							
						}
						else if(i == 1) // �X�{Lower����
						{
								order[n++] = 1;
							
						}
						else if(i == 2) // �X�{Proper����
						{
								order[n++] = 2;
							
						}
						else if(i == 3) // �X�{Reverse����
						{
								order[n++] = 3;
								
						}
				}
		}
		if(strstr(input,"<Newline>")!=NULL) // �X�{Newline����
		{
				order[n++] = 4;
		
		}
	
		if(strstr(input,"<Insert char = ")!=NULL) // �X�{Insert����
		{
				order[n++] = 5;
			
		}

		// �p��mark[]�}�C�����`�X,�p�G>=1,�h��ܸӦr��X�{���Һ������u�@��
		
	
		int order_len,tag;
		
		order_len = n;

		if(order_len >= 1) 
		{
				tag = order[order_len-1];
				if(tag >=0 && tag<=3)
				{
						
								// ���O�O���Y�����Ҫ����Ц�m
								test1 = strstr(input,array_1[tag]);
								test2 = strstr(input,array_2[tag]);
								// ��X���Ҧb�r����Ӧ�m
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
				//���ĤT��"'"�M�ĥ|��"'"��,���O�O���L�̪���m
				if(find == 3)
						temp1 = pch-input;
				else if(find == 4)
						temp2 = pch-input;
				pch = strstr(pch+1,"'");
		}
		//�O��number�O�X���,�ëŧi��n��ƪ��r��
		ch_len = temp2-temp1;
		char temp[ch_len];

		while(input[i] != '\0')
		{
				if(i == pos)
				{
						i = i+len; // i�|�]��ҭn��character
						ch = input[i];

						i = i+(temp1-i)+1; // i�|�]��ĤT��"'",�ҥH�ݭn�A�[1�~�|�O�n��number
						
						//�x�snumber��r�ꤤ
						for(k=0;k<ch_len;k++)
								temp[k] = input[i++];

						times = atoi(temp);//�ഫ�r�ꬰint��ƫ��A
						i = end+1;//end�ҥN����m��">",�Gi�����A�[1

						//�Ncharater��for�j��s�Jresult��
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
				if(i == start_pos) // i��m�]��<Proper>,���L
						i = i+len;
				else if(i == end_pos) // i��m�]��</Proper>,���L
						i = i+len+1;
                // ��i�b<Proper>�M</Proper>������
				if(i >= (start_pos+len) && i< end_pos)
				{
						if(i == (start_pos+len)) // <Proper>���ҫ᪺�Ĥ@�Ӧr��j�g
								input[i] = toupper(input[i]);
						if(input[i] == ' ') 
								input[i+1] = toupper(input[i+1]); // �ťի�Ĥ@�Ӧr��j�g
				}
				result[j++] = input[i++];
		}
		fprintf(fp2,"%s",result);


}

void Upper(char input[],int start_pos,int end_pos)
{
		int i=0,j=0,len;
		char result[100]={0}; //�r���k�s
		
		len = strlen("<Upper>");		
		while(input[i] != '\0')
		{
				if(i == start_pos) // i��m�]��<Upper>,���L
						i = i+len;
				else if(i == end_pos) // i��m�]��</Upper>,���L
						i = i+len+1;
				// ��i�b<Upper>�M</Upper>������,input[i]��toupper
				if(i >= (start_pos+len) && i< end_pos)
						input[i] = toupper(input[i]);
				result[j++] = input[i++];
		}
		
		fprintf(fp2,"%s",result);
}
void Lower(char input[],int start_pos,int end_pos)
{
		int i=0,j=0,len;
 		char result[100]={0};//�r���k�s
		
		len = strlen("<Lower>");
		while(input[i] != '\0')
		{
				if(i == start_pos) // i��m�]��<Lower>,���L
						i = i+len;
				else if(i == end_pos) // i��m�]��</Lower>,���L
						i = i+len+1;
				// ��i�b<Lower>�M</Lower>������,input[i]��tolower
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

		reverse_len = end_pos - (start_pos+len); // �n���઺�r�����
		char temp[reverse_len];

		while(input[i] != '\0')
		{
				if(i == start_pos)
						i = i+len;
				else if(i == end_pos)
						i = i+len+1;

				//����n���઺�r��ϵ��x�s�btemp[]
				if(i == (start_pos+len))
				{
						n=i; // ���F���]�r���m��i,�b�o�O������
						for(k=reverse_len-1;k>=0;k--)
								temp[k] = input[n++];
				}
				
				if(i >= (start_pos+len) && i < end_pos) //�|�i�o�Ӱj�� �r����� �� EX:�nreverse���r����׬�4,�i�J���j�馸�ƫh��4
						input[i] = temp[m++];
				
				result[j++] = input[i++];
		}

		fprintf(fp2,"%s",result);
}
				
















