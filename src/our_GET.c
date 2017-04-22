#include "../headers/our_GET.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>
#define CHUNCK_SIZE 20
#define DEFAULT_PATH "serverpath/"

void get_file_by_GET_command(char * getCommand) {
	char path[50];
	if (!(getCommand[0] == 'G' && getCommand[1] == 'E' && getCommand[2] == 'T')) {
		printf("Invalid HTTP request\n");
	} else
	{
		int i ;
		int len = strlen(getCommand);
		for (i = 0; i <  len - 4; ++i) {
            path[i] = getCommand[i + 4];
		}
		path[i] = '\0';
		get_file_by_path(path);
	}
}
void get_file_by_path(char * path) {

	char server_path[100];
	strcpy(server_path, DEFAULT_PATH);
	strcat(server_path, path);
	FILE * f = fopen(server_path, "r");
	if (f == NULL) {
		char error_command[50] = "GET error404.html";
		get_file_by_GET_command(error_command);

	} else {
//		printf("File found!\n");
		printf("\n");
		print_requested_file(server_path);
		fclose(f);
	}

}

void print_requested_file(char * path) {
	FILE * file = fopen(path, "r");
	char buf[CHUNCK_SIZE];
	int nbytes;
	while ((nbytes = fread(buf, 1, sizeof buf, file)) > 0) {
		printf("%s", buf);
	}
	fclose(file);
}

void send_requested_file() {

}
