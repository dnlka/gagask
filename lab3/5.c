#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <regex.h>

void WWF(char* name, char* filetext)
{
	FILE* file = fopen(name, "r");
        int index = 0;
	char gt;
        while (gt != EOF)
        {
        	gt = getc(file);
                filetext[index] = gt;
                index += 1;
	}
	filetext[index - 1] = 0;
	fclose(file);
}

void find(char *startDir, regex_t* regx){
	char str[10000],nextDir[200]={0};
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
			find(nextDir, regx);
			nextDir[len] = '\0';
		}
		if(de->d_type == DT_REG && strcmp(de->d_name,"5.c") && strcmp(de->d_name,"a.out")){
			len=strlen(nextDir);
			strcat(nextDir,"/");
			strcat(nextDir,de->d_name);
			WWF(nextDir,str);
			if (regexec(regx, str, 0, NULL, 0) == 0) remove(nextDir);
			nextDir[len]='\0';
		}

		de = readdir(dir);
	}
	closedir(dir);
}


int main(){
	char * regexString = ".*mail.*";
        regex_t regexCompiled;
        regcomp(&regexCompiled, regexString, REG_EXTENDED);
	char str[PATH_MAX];
	getcwd(str,PATH_MAX);
	find(str,&regexCompiled);
        regfree(&regexCompiled);
}
