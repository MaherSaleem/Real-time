/*
 * MessageQ.h
 *
 *  Created on: May 6, 2017
 *      Author: mohammed
 */


#include <linux/msg.h>
//#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#define messageQ_KEY 500
#define PUBLIC_PORT 1
struct msg
{
	long int type;  // pid
};


