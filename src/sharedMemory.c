/*
 * sharedMemory.c
 *
 *  Created on: Apr 27, 2017
 *      Author: mohammed
 */

#include <sys/types.h>
#include <sys/shm.h>
#include <stdio.h>

#define MEM_SIZE 1024

int open_segment(key_t keyval, int segsize) {
	int shm_id;
	if ((shm_id = shmget(keyval,segsize, IPC_CREAT|0660)) == -1)
		return -1;
	return shm_id;
}

