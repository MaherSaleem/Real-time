/*
 * MessageQ.h
 *
 *  Created on: May 6, 2017
 *      Author: maher
 */


#include <sys/msg.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>

#define messageQ_KEY 500
#define PUBLIC_PORT 1


struct msg
{
	long int type;  // pid
};

struct msg getUserCommand(int pid);

void sendUser(int pid);
