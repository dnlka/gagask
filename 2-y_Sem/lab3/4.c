#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct dirt{
	char* name;
	int k;
}dirt;

void find(char *startDir, dirt* arr){
	char nextDir[200]={0};
	int len;
	strcpy(nextDir, startDir);
	DIR *dir = opendir(startDir);
	if(!dir)
		return;
	struct dirent *de = readdir(dir);
	while(de){
		if(de->d_type == DT_DIR && strcmp(de->d_name, ".")  && strcmp(de->d_name, ".."))
		{
			len = strlen(nextDir);
			strcat(nextDir, "/");
			strcat(nextDir,de->d_name);
			find(nextDir, arr);
			nextDir[len] = '\0';
		}
		if(de->d_type == DT_REG)
            		for(int i=0;i<20;i++)
			{
				if (!strcmp(de->d_name,arr[i].name)) 
					{arr[i].k++;
					len=strlen(nextDir);
					strcat(nextDir,"/");
					strcat(nextDir,de->d_name);
					remove(nextDir);
					nextDir[len]='\0';
					break;}
				else
					if(strlen(arr[i].name)==0){
						strcpy(arr[i].name,de->d_name);
						arr[i].k=1;
						break;}
			}
		de = readdir(dir);
	}
	closedir(dir);
}


int main(){
	dirt* arr=(dirt*)malloc(20*sizeof(dirt));
	for(int i=0;i<20;i++)
	arr[i].name=(char*)calloc(30,1);
	char str[PATH_MAX];
	getcwd(str,PATH_MAX);
	find(str,arr);
	for(int i=0;i<20;i++) if (arr[i].k>1) printf("%s - %d\n",arr[i].name,arr[i].k);
}

