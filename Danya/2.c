#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ctype.h>

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


void search(char* name){
        DIR* dir = opendir(name);
	int flag=0;
	if (!dir){
		printf("Wrong path!\n");
		return;
	}
        struct dirent* de = readdir(dir);
        while (de)
        {
                if (!strncmp(de -> d_name, ".", 1) || !strncmp(de -> d_name, "..", 2)){
			de = readdir(dir);
			continue;
		}
                if (de->d_type==DT_REG && strcmp(de -> d_name, "a.out") && strcmp(de -> d_name, "2.c")){
                        char* s = (char*)malloc(3);

                        for (int i = 0; i < strlen(de -> d_name); i++)
                                if (isalpha((de -> d_name)[i])){
                                        s[flag] = (de -> d_name)[i];
                                        flag+=1;
                                        break;
                                }
                        for (int i = 0; i < strlen(de -> d_name); i++)
                                if (isdigit((de -> d_name)[i])){
                                        s[flag] = (de -> d_name)[i];
                                        flag+=1;
                                        break;
                                }
                        s[flag]=0;
                        flag=0;
                        char* way = (char*)calloc(strlen(de -> d_name) + strlen(name) + 3, sizeof(char));
                        strcat(way, name);
                        strcat(way, "/");
                        strcat(way, s);
			char text[10000];
			copy(de -> d_name, text);
			char cpy[1000];
			strcpy(cpy, de->d_name);
			remove(de->d_name);
                        if (!opendir(s))
				mkdir(way, S_IRWXU);
			strcat(way, "/");
			strcat(way, cpy);
			FILE* file = fopen(way, "w");
			fprintf(file, "%s", text);
			fclose(file);
			free(way);
			free(s);
                }
                de = readdir(dir);
        }
	closedir(dir);
}


int main()
{
	char* name = (char*)malloc(PATH_MAX);
	getcwd(name, PATH_MAX);
        search(name);
	free(name);
        return 0;
}

