#include <stdio.h>
#include <stdlib.h>
#include "../headers/semafors.h"
#include "../headers/worker.h"
#include "../headers/sharedMemory.h"
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
#include <sys/shm.h>



#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#include "../headers/Globals.h"
#include "../headers/MessageQ.h"

#define VERBOS 1
int checkallsem(int semid);
char *path;
int oldpid;

int restartVar=0;
int flagstop=0;


void (* old_handler)(int);


void stop_server(int sig){
	flagstop=1;
	signal(SIGINT , stop_server);
}


void restart_server(int sig){
	oldpid=getpid();
	restartVar=1;
	char buffer[10];
	sprintf(buffer, "%d", oldpid);
	strcat(path, " ");
	strcat(path,buffer);
	printf("%s\n",path);
	system(path);



}

#define VERBOS 1

int checkallsem(int semid)
{
	int i;
	int current_value;
	for (i = 0; i < c.n; i++) {
		current_value = get_semafor_value(semid, i);
		printf("Sempgores free are %d\n" , current_value);
		if (current_value != c.m)
			return 1;

	}

	return 0 ;
}


int main(int argc ,char *argv[]) {

	c = get_server_configrations();
	//read the configrations
	print_configrations(c);


	if (argc >=2) {
			signal(SIGTERM, stop_server);
			signal(SIGHUP, restart_server);
			setsid();
			printf("%s\n", argv[1]);
			int myold = atoi(argv[1]);
			kill(myold, SIGTERM);
			printf("HIIIIIIIII\n");

	}


	int i;
	int r = -1; // the choosen worker to handle the request
	process = (int *) malloc(c.n * sizeof(int));

	//create semaphore set with length n
	int semid = get_semafor(semKey, c.n);

	//set the inirial value for each semphore to m
	for (i = 0; i < c.n; i++) {
		init_sem(semid, i, c.m);
	}

	// create sharedMemory
	int shm_id = open_segment(shmKey, MEM_SIZE);

	//attaching process address space to this sh mem
	int * mem_base_address = (int *)shmat(shm_id, NULL, 0);


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
			handle_connection();
		} else {
			process[i] = pid; //store the id of the child
			mem_base_address[i] = pid; // now max index is 255

//			printf("parent\n");
		}

	}

	printf("#####################################\n");
	//print the ids of children
	for (i = 0; i < c.n; i++)
		printf("Worker#%d is created with id %d\n",i, process[i]);
	printf("#####################################\n");


	//create set for fds to check if there is any client want to
	// to connect to the server
	fd_set rfds;
	int ret_val;

	/* Watch stdin (fd 0) to see when it has input. */
	struct timeval waitTime = { 0, 0 };

	if (VERBOS)
		printf("Code Reached Here:2\n");

// now waiting for any connection to assign it to a Worker
	r=1;
	while (!flagstop) {

		int mypid=getpid();
		signal(SIGTERM, stop_server);
		signal(SIGHUP, restart_server);
		signal(SIGUSR1, restart_server);

		FD_ZERO(&rfds);
		FD_SET(fd, &rfds);

		ret_val = select(fd + 1, &rfds, NULL, NULL, &waitTime);

		//printf("%d\n", ret_val);
		int val;

		if (ret_val >0) {
			printf("$$$$$$%d\n", ret_val);

			printf("MMMMMMMMMMMMMMMMM\n");
			srand(time(NULL));   // should only be called once
			printf("MMMMMMMMMMMMMMMMM\n");

//			r = rand() % c.n;   // TODO make algorithm to choose r
			r=(r+1) % c.n;// TODO remove this
			val = get_semafor_value(semid, r);
			if (VERBOS)
				printf("r choosed is :%d\n", r);

			sendUser(process[r]);
			printf("YYY1\n");
			mem_base_address[c.n+7] = '*';

			while(mem_base_address[c.n+7] == '*');
			printf("YYY2\n");

			if (VERBOS)
				printf("Code Reached Here:3\n");


		}
	}

	while (checkallsem(semid));
	printf("Signal Handeld");
	exit(0);


	out: while (1) {
		sleep(1);
	}

	return 0;

}
