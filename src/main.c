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
#include "../headers/worker.h"
#include "../headers/setup_configrations.h"
#include <unistd.h>

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>



int main(void) {

	configs c = get_server_configrations();
	print_configrations(c);
	int pos = 0, i;
	int r = -1;
	long process[c.n];
	long semid = get_semafor(semKey, c.n);

	for (i = 0; i < c.n; i++)
		init_sem(semid, i, c.m);





	// Creat array of children
	for (i = 0; i < c.n; i++) {
		switch (fork()) {

			case -1: //fork error;
				printf("[ERROR] - fork()\n");
				exit(EXIT_FAILURE);

			case 0: //child
				process[pos] = getpid();
				pos++;

				//exit(EXIT_SUCCESS);
				goto out;

			default:
				break;
		}


	}


	for (i = 0; i < c.n; i++)
		printf("%ld\n", process[i]);


	int fd, nBytes;
	char buffer[1024];
	struct sockaddr_in serverAddr, clientAddr;
	socklen_t addr_size, client_addr_size;


	/*Create UDP socket*/
	fd = socket(AF_INET, SOCK_STREAM, 0);

	/*Configure settings in address struct*/
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(c.p);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	// memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

	/*Bind socket with address struct*/
	bind(fd, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

	/*Initialize size variable to be used later on*/
	addr_size = sizeof(clientAddr);


	if (listen(fd, 1000) < 0) {
		perror("listen");
		exit(1);
	}

	printf("\ns\n");

	fd_set rfds;
	int retval;

	/* Watch stdin (fd 0) to see when it has input. */
	struct timeval waitTime = {0, 0};


	/* Don’t rely on the value of tv now! */
	while (1) {

		FD_ZERO(&rfds);
		FD_SET(fd, &rfds);


		retval = select(fd + 1, &rfds, NULL, NULL, &waitTime);


		//printf("%d\n", retval);
int val ;
		if (FD_ISSET(fd, &rfds)) {

			srand(time(NULL));   // should only be called once
			do {
				r = rand() % c.n;
				//printf("%d\n", r);
				val = get_semafor_value(semid, r);
			} while (val < 0);
			int newfd; /* returned by accept() */
			newfd = accept(fd, (struct sockaddr*) &clientAddr, &addr_size);
			printf("I am here\n");


		}
	}

	out:
	while (1){


}

	return 0;




}



