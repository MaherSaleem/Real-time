#include "../headers/worker.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../headers/semafors.h"
#include <stdio.h>
#include <stdlib.h>
#include "../headers/semafors.h"
#include "../headers/worker.h"
#include "../headers/setup_configrations.h"
#include "../headers/server_signals.h"
#include "../headers/sharedMemory.h"

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
#include "../headers/Globals.h"
#include "../headers/MessageQ.h"


void child (int r){

	int  nBytes;
	char buffer[1024];

	int shm_id = open_segment(shmKey, MEM_SIZE);
	int * mem_base_address = (int *)shmat(shm_id, NULL, 0);

	printf("%%%%%%%%%%%%%%%%%% INSIDE HANDLING REQUEST%%%%%%%%%%%%%%%%\n");
	//print current value of semafor
	int semid = get_semafor(semKey, c.n);
	int current_value = get_semafor_value(semid, r);
	printf("current value of semafor is %d\n", current_value);

	//Acquire
	current_value = acquire_sem(semid, r);
	printf("new value of semafor is %d\n", current_value);

	//accept
	struct sockaddr_in clientAddr;
	socklen_t addr_size;
	addr_size = sizeof(clientAddr);
	int newfd = accept(fd, (struct sockaddr*) &clientAddr, &addr_size);
	printf("1=%c\n",mem_base_address[c.n+7 ]);
	mem_base_address[c.n+7] = '_';
	printf("2=%c\n",mem_base_address[c.n+7 ]);
	//read the GET command from client
	if((nBytes = read(newfd, buffer, 1024)) < 0) {
	        perror("read");
	        exit(1);
	}
	else{
//		printf("\nClient has requested %s\n", buffer);
		////////////////////

		int j,k=4;
		int len = strlen(buffer);
		char	buff2 [1024] = "GET ";
		for (j = 5; j < len; ++j) {
			if (buffer[j] == ' ') break;
			buff2[k++]= buffer[j];

		}
		buff2[k] = '\n';
		/////////////////////
		get_file_by_GET_command(buff2, newfd);//
	}

	//send html file

	//relase
	current_value = release_sem(semid, r);
	printf("again value of semafor is %d\n", current_value);
	addr_size = sizeof(clientAddr);
	printf("%%%%%%%%%%%%%%%%%% Finished HANDLING REQUEST%%%%%%%%%%%%%%%%\n");


}


void handle_connection(){
	printf("!!!Inside handler\n");
	while(1){
		struct msg p = getUserCommand(getpid());

		//attaching process address space to this sh mem
		int r = get_process_index_by_id();
		if (r == -1)
			perror("PID not found");
		else
			child(r);
	}
}


int get_process_index_by_id(){
	// create sharedMemory
	int shm_id = open_segment(shmKey, MEM_SIZE);
	int * mem_base_address = (int *)shmat(shm_id, NULL, 0);
	int pid = getpid();
//	printf("<<%d>>\n",pid);
	int i = 0;
	for (i = 0; i < c.n; ++i) {
//		printf("((%d))\n",mem_base_address[i]);
		if (pid == mem_base_address[i])
			return i;
	}
	return -1;

}
