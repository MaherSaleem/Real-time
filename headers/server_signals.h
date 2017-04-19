/*
 *
 */


#ifndef SERVER_SIGNALS_H_
#define SERVER_SIGNALS_H_
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>



void reload_config_file(int sig);
void restart_server(int sig);
void stop_server(int sig);




#endif
