#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <regex.h>

void copy(char* name, char* text){
        FILE* file = fopen(name, "r");
        int index = 0;
        char c;
        while (c != EOF)
        {
                c = getc(file);
                text[index] = c;
                index += 1;
        }
        text[index - 1] = 0;
        fclose(file);
}


void find(char* dirpath, regex_t* regx){
	char way[10000]="";
	strcpy(way, dirpath);
	int len;
	DIR* dir=opendir(dirpath);
	if (dir){
		struct dirent* de = readdir(dir);
        	while (de){
			if(de->d_type == DT_DIR && strcmp(de->d_name, ".")  && strcmp(de->d_name, "..")){
            			len=strlen(way);
            			strcat(way, "/");
            			strcat(way, de->d_name);
           			find(way, regx);
            			way[len] = '\0';
			}
			if (de->d_type==DT_REG && strcmp(de -> d_name, "a.out") && strcmp(de -> d_name, "6.c")){
				len=strlen(way);
                                strcat(way, "/");
                                strcat(way, de->d_name);
				char text[10000];
				copy(way, text);
				if (regexec(regx, text, 0, NULL, 0))
					remove(way);
				way[len]='\0';
			}
			de=readdir(dir);
		}
		closedir(dir);
	}
}


int main(){
	char * regexString = "[A-Za-z0-9_-]+,[A-Za-z0-9_-]+@[a-z]+\\.[a-z]+";
        regex_t regexCompiled;
        regcomp(&regexCompiled, regexString, REG_EXTENDED);
	char str[PATH_MAX];
	getcwd(str,PATH_MAX);
	find(str, &regexCompiled);
        regfree(&regexCompiled);
	return 0;
}
