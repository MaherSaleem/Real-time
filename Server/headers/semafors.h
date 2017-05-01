/*
 * Stack.h
 *
 *  Created on: MARCH, 2017
 *
 */

#ifndef SEMAFOR_H_
#define SEMAFOR_H_

#define semKey 200

union semun {
	int val;
	struct semid_ds *buf;
	int *array;
	struct seminfo *__buf;

};

int get_semafor(int Key, int size);
int get_semafor_value(int semid, int semnum);
void init_sem(int semid, int semnum, int init_value);
int acquire_sem(int semid, int semnum);
int release_sem(int semid, int semnum);

#endif /* SEMAFOR_ */
