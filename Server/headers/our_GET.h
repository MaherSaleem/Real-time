/*
 *
 */


#ifndef OUR_GET_H_
#define OUR_GET_H_
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>



#define CHUNCK_SIZE 20
#define DEFAULT_PATH "serverpath/"

void get_file_by_GET_command(char * getCommand, int fd);
void get_file_by_path(char * path, int fd) ;
void print_requested_file(char * path, int fd) ;
void send_requested_file(char * path, int newFd) ;

#endif
