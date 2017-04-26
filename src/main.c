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
#include "../headers/server_signals.h"
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
#include <signal.h>


#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#include "../headers/Globals.h"

#define VERBOS 1


int main(void) {

	c = get_server_configrations();
	//read the configrations
	print_configrations(c);

	int pos = 0;
	int i;
	int r = -1; // the choosen worker to handle the request
	process = (int *) malloc(c.n * sizeof(int));

	//create semaphore set with length n
	int semid = get_semafor(semKey, c.n);

	//set the inirial value for each semphore to m
	for (i = 0; i < c.n; i++) {
		init_sem(semid, i, c.m);
	}


	if (VERBOS)
		printf("Code Reached Here:1\n");

	int nBytes;
	char buffer[1024];

	/*Create TCP socket*/
	fd = socket(AF_INET, SOCK_STREAM, 0);

	/*Configure settings in address struct*/
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(c.p);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	/*Bind socket with address struct*/
	bind(fd, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

	/*Initialize size variable to be used later on*/
	addr_size = sizeof(clientAddr);

	if (listen(fd, 1000) < 0) {
		perror("listen");
		exit(1);
	}



	// create array of children
	for (i = 0; i < c.n; i++) {
		int pid = fork();

		if (pid == -1) {
			perror("fork");
			exit(EXIT_FAILURE);

		} else if (pid == 0) {

//			printf("%d\n", getpid());
			signal(SIGUSR2, handle_connection); //connect the signal for each child to handle connection
			goto out;
		} else {
			process[i] = pid; //store the id of the child
//			printf("parent\n");
		}

	}

	//print the ids of children
	for (i = 0; i < c.n; i++)
		printf("%d\n", process[i]);


	//create set for fds to check if there is any client want to
	// to connect to the server
	fd_set rfds;
	int ret_val;

	/* Watch stdin (fd 0) to see when it has input. */
	struct timeval waitTime = { 0, 0 };

	if (VERBOS)
		printf("Code Reached Here:2\n");

// now waiting for any connection to assign it to a Worker
	while (1) {

		FD_ZERO(&rfds);
		FD_SET(fd, &rfds);

		ret_val = select(fd + 1, &rfds, NULL, NULL, &waitTime);

		//printf("%d\n", ret_val);
		int val;
		if (FD_ISSET(fd, &rfds)) {

			srand(time(NULL));   // should only be called once

			r = rand() % c.n;   // TODO make algorithm to choose r
			val = get_semafor_value(semid, r);
			if (VERBOS)
				printf("r choosed is :%d\n", r);
			kill(process[r], SIGUSR2);
			if (VERBOS)
				printf("Code Reached Here:3\n");

			exit(1);
		}
	}

	out: while (1) {
		sleep(1);
	}

	return 0;

}




