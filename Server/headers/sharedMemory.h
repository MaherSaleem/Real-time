/*
 * sharedMemory.h
 *
 *  Created on: Apr 28, 2017
 *      Author: mohammed
 */

#include <sys/types.h>
#include <sys/shm.h>
#include <stdio.h>

#define MEM_SIZE 1024
#define shmKey 200


int open_segment(key_t keyval, int segsize);
