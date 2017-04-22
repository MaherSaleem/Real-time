/*
 * Stack.h
 *
 *  Created on: MARCH, 2017
 *
 */


#ifndef SEMAFOR_H_
#define SEMAFOR_H_

#define semKey 200




/*
union semun {
	int val; */
/* Value for SETVAL *//*

	struct semid_ds *buf; */
/* Buffer for IPC_STAT, IPC_SET *//*

	int *array; */
/* Array for GETALL, SETALL *//*

	struct seminfo *__buf; */
/* Buffer for IPC_INFO
	 (Linux-specific) *//*

};
*/





int get_semafor(int Key , int size);
int get_semafor_value(int semid, int semnum);
void init_sem(int semid, int semnum, int init_value);
int acquire_sem(int semid, int semnum);
int release_sem(int semid, int semnum);



#endif /* SEMAFOR_ */
