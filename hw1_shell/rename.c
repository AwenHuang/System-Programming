#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
int comp(const void*a,const void*b);

int main(int argc,char *argv[])
{
		DIR *dp; // directory pointer
		struct dirent *dirp;
		int i,file_num;
		char *files[100]; // �s���ɮת����а}�C
		char old_path[100],new_path[100]; // �s���ɮת����|

		char *ptr; // �Ψӧ�"."����m
		file_num = 0; // �������X���ɮ�
		dp = opendir(argv[argc-1]);

		while((dirp = readdir(dp))!=NULL)
		{
				if(strcmp(dirp->d_name,".")==0 || strcmp(dirp->d_name,"..")==0)
						continue;
				files[file_num] = (char*)malloc(sizeof(100));

				strcpy(files[file_num],dirp->d_name);
				file_num++;
				
		}
		if(file_num > 0)
		{
				qsort(files,file_num,sizeof(files[0]),comp);
				for(i=0;i<file_num;i++)
				{
						sprintf(old_path,"%s/%s",argv[argc-1],files[i]);
						ptr = strchr(files[i],'.');
						sprintf(new_path,"%s/%s_%d%s",argv[argc-1],argv[argc-2],i+1,ptr);
						rename(old_path,new_path);
				}
		}
		else
				printf("No files in %s\n",argv[argc-1]);
		return 0;
}
int comp(const void*a,const void*b)
{
		return strcmp(*(char**)a,*(char**)b);

}

