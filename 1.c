#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

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


void find(char name[])
{
	int buffer = 10000;
        DIR* dir = opendir(name);
	if (!dir) {printf("Uncorrect path!\n"); return;}
        struct dirent* ent = readdir(dir);
        while (ent)
        {
                if (!strncmp(ent -> d_name, ".", 1) || !strncmp(ent -> d_name, "..", 2)) {ent = readdir(dir); continue;}
                if (ent->d_type==DT_REG && strcmp(ent -> d_name, "a.out") && strcmp(ent -> d_name, "1.c"))
                {
                        char* s = (char*)malloc(2);
			s[0] = *(ent -> d_name);
			s[1] = 0;

                        char* path = (char*)calloc(strlen(ent -> d_name) + strlen(name) + 2, sizeof(char));
                        strcat(path, name);
                        strcat(path, "/");
                        strcat(path, s);

			char* textfile = (char*)malloc(buffer);

                        if (!opendir(s)) mkdir(path, S_IRWXU);
			WWF(ent -> d_name, textfile);

			strcat(path, "/");
			strcat(path, ent -> d_name);

			FILE* file = fopen(path, "w");
			fprintf(file, "%s", textfile);
			fclose(file);

			remove(ent -> d_name);
			free(path);
			free(s);
                }
                ent = readdir(dir);
        }
	closedir(dir);
}


int main()
{
	char* name = (char*)malloc(PATH_MAX);
	getcwd(name, PATH_MAX);
        find(name);
	free(name);
        return 0;
}


