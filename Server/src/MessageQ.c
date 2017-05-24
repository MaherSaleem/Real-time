#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#include "../headers/MessageQ.h"


	struct msg getUserCommand(int pid){
		printf("%d !!!Inside getUserCommand\n" , getpid());
		struct msg p;
		int m = msgget(messageQ_KEY,0666|IPC_CREAT); // since the queue is created before,it just will create it
		printf("111111\n");
		msgrcv(m, &p, sizeof(p)-4, getpid(), 0); // receive fileName at type=1
		printf("222222\n");

		return p;
	}

	void sendUser(int pid){
		printf("inside send message to worker\n");
		struct msg p;
		int m = msgget(messageQ_KEY,0666|IPC_CREAT); // since the queue is created before,it just will create it
		p.type = pid;
		msgsnd(m,&p,sizeof(p) -4 ,0);// send pointer to p on the queue
		printf("finished send message to worker\n");
	}
