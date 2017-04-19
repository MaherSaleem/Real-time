/*
 *
 */


#ifndef SETUP_CONFIGRATION_H_
#define SETUP_CONFIGRATION_H_
#include <stdio.h>
#include <stdlib.h>

#define CONFIGRATION_FILE_NAME "config"

struct configs {
	int n; // number of workers
	int m; //number of connections
	int p; // port number
};

typedef struct configs configs;


/*
 * this function will return a struct of
 * configrations the stored inside CONFIGRATION_FILE
 */
configs get_server_configrations();


void print_configrations(configs c);
#endif /* SETUP_CONFIGRATION */
