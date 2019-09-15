#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

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
                if (de->d_type==DT_REG && strcmp(de -> d_name, "a.out") && strcmp(de -> d_name, "1.c")){
                        char* s = (char*)malloc(2);
			s[0] = *(de -> d_name);
			s[1] = 0;

                        char* way = (char*)calloc(strlen(de -> d_name) + strlen(name) + 2, sizeof(char));
                        strcat(way, name);
                        strcat(way, "/");
                        strcat(way, s);
			char text[10000];
                        if (!opendir(s))
				mkdir(way, S_IRWXU);
			copy(de -> d_name, text);
			strcat(way, "/");
			strcat(way, de -> d_name);
			FILE* file = fopen(way, "w");
			fprintf(file, "%s", text);
			fclose(file);

			remove(de -> d_name);
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

