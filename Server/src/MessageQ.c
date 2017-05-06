/*
 * MessageQ.c
 *
 *  Created on: May 6, 2017
 *      Author: mohammed
 */

/*
	The server has a listing type which is 1
	it open a file and returns data of file to the client
*/

#include <stdio.h>
#include <stdlib.h>
#include <linux/msg.h>
//#include <fcntl.h>
#include "../headers/MessageQ.h"



	struct msg getUserCommand(int pid){
		struct msg p;
		int m = msgget(messageQ_KEY,0666|IPC_CREAT); // since the queue is created before,it just will create it
		msgrcv(m, &p, sizeof(p)-4, PUBLIC_PORT, 0); // receive fileName at type=1
		return p;
	}

	struct msg sendUser(int pid){
		struct msg p;
		int m = msgget(messageQ_KEY,0666|IPC_CREAT); // since the queue is created before,it just will create it
		p.type = pid;
		msgsnd(m,&p,sizeof(p) -4 ,0);// send pointer to p on the queue
	}

