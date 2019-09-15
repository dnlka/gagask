#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <regex.h>

void copy(char *name, char *text){
        FILE* file = fopen(name, "r");
		fgets(text, 1000, file);
		text[strlen(text) - 1] = '\0';
        fclose(file);
}


void find(char* dirpath, regex_t* regx){
	char way[1000]="";
	strcpy(way, dirpath);
	int len, i;
	DIR* dir=opendir(way);
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
			    if (de->d_type == DT_REG){
			    	len=strlen(way);
                    strcat(way, "/");
                    strcat(way, de->d_name);
			    	char text[1000];
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
	char Dir[100];
	char str[PATH_MAX];
	fgets(Dir, PATH_MAX, stdin);
	Dir[strlen(Dir) - 1] = '\0';
	getcwd(str, PATH_MAX);
	strcat (str, Dir);
	find(str, &regexCompiled);
        regfree(&regexCompiled);
	return 0;
}
