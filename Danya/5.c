#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
void search(char* dirpath){
	char way[500];
	char random[500]="qwertyuiopasdfghjklzxcvbnm";
	strcpy(way, dirpath);
	DIR *dir=opendir(dirpath);
	if (dir){
		int a=strlen(way);
		for (int i=0; i<5; i++){
			strcat(way, "/");
			char* s=(char*)malloc(2*sizeof(char));
			s[0]=random[i];
			s[1]=0;
			strcat(way, s);
			remove(s);
			if (!opendir(s))
				mkdir(way, S_IRWXU);
			strcat(way, "/");
			strcat(way, s);
			FILE* file=fopen(way, "w");
			fprintf(file, "%s", "ddddddd,bbb@mail.ru");
			fclose(file);
			way[a]='\0';
			free(s);
		}
		for (int i=5; i<10; i++){
                        strcat(way, "/");
                        char* s=(char*)malloc(2*sizeof(char));
                        s[0]=random[i];
                        s[1]=0;
			strcat(way, s);
			remove(s);
                        if (!opendir(s))
                                mkdir(way, S_IRWXU);
                        strcat(way, "/");
                        strcat(way, s);
                        FILE* file=fopen(way, "w");
                        fprintf(file, "%s", "cccccc,gggg@mail.ru");
			fclose(file);
                        way[a]='\0';
			free(s);
                }
		for (int i=10; i<15; i++){
                        strcat(way, "/");
                        char* s=(char*)malloc(2*sizeof(char));
                        s[0]=random[i];
                        s[1]=0;
			strcat(way, s);
			remove(s);
                        if (!opendir(s))
                                mkdir(way, S_IRWXU);
                        strcat(way, "/");
                        strcat(way, s);
                        FILE* file=fopen(way, "w");
                        fprintf(file, "%s", "for delete");
			fclose(file);
                        way[a]='\0';
			free(s);
                }
		for (int i=15; i<20; i++){
                        strcat(way, "/");
                        char* s=(char*)malloc(2*sizeof(char));
                        s[0]=random[i];
                        s[1]=0;
			strcat(way, s);
			remove(s);
                        if (!opendir(s))
                                mkdir(way, S_IRWXU);
                        strcat(way, "/");
                        strcat(way, s);
                        FILE* file=fopen(way, "w");
                        fprintf(file, "%s", "delete@mail.ru");
			fclose(file);
                        way[a]='\0';
			free(s);
                }
	}
	closedir(dir);
}

int main(){
	char* namen = (char*)malloc(PATH_MAX);
	getcwd(namen, PATH_MAX);
	search(namen);
	free(namen);
	return 0;
}

