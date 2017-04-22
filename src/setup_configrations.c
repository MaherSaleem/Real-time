/*
 * setup_configrations.c
 *
 *  Created on: Apr 19, 2017
 *      Author: maher
 */

#include "../headers/setup_configrations.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>



void print_configrations(configs c){

	printf("Number of workers is %d\n", c.n);
	printf("Number of Connections is %d\n", c.m);
	printf("Port is %d\n",c.p);
}

/*
 * this function will return a struct of
 * configrations the stored inside CONFIGRATION_FILE
 */
configs get_server_configrations(){

	struct configs ret;//create empty struct

	FILE * config_file = fopen(CONFIGRATION_FILE_NAME, "r");

	assert(config_file != NULL);

	char temp[20];
	fscanf(config_file,"%s",temp);
	fscanf(config_file,"%d",&ret.n);

	fscanf(config_file,"%s",temp);
	fscanf(config_file,"%d",&ret.m);

	fscanf(config_file,"%s",temp);
	fscanf(config_file,"%d",&ret.p);


	return ret;
}
