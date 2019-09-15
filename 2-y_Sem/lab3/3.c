#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#define BUFFER 100


void find(char* way, char* word)
{
	DIR* dir = opendir(way);
	struct dirent* ent = readdir(dir);
	while (ent)
	{
		if (!opendir(ent -> d_name) && !strncmp(word, ent -> d_name, strlen(word))) remove(ent -> d_name);
		ent = readdir(dir);
	}
	closedir(dir);
}


int main()
{
	char* word = (char*)malloc(BUFFER);
	fgets(word, BUFFER, stdin);
	*(strrchr(word, '\n' )) = 0;

	char* name = (char*)malloc(BUFFER);
	getcwd(name, 100);

	find(name, word);
	free(name);
	free(word);
	return 0;
}

