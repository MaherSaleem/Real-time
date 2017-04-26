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

void get_file_by_GET_command(char * getCommand);
void get_file_by_path(char * path) ;
void print_requested_file(char * path) ;
void send_requested_file() ;

#endif
