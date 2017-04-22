/*
 ============================================================================
 Name        : Real-time-project.c
 Author      : Maher
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "../headers/semafors.h"
#include "../headers/setup_configrations.h"

int main(void) {

	configs c = get_server_configrations();
	print_configrations(c);
	printf("test");
	return 0;
}
