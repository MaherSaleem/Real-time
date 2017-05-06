#include <stdio.h>

#include <sys/types.h>
#include <sys/sem.h>
#include <semaphore.h>
#include "../headers/semafors.h"




/*
 * This function is used to create/get set of semaphor,
 * @return semaphor id
 */
int get_semafor(int Key, int size){
	return semget(Key, size, IPC_CREAT | 0660);
}


/*
 * this function is used to get the current value of an elm inside the set of semafors
 */
int get_semafor_value(int semid, int semnum) {
	return semctl(semid, semnum, GETVAL, 0);
}


/*
 * initilizes singla semafor
 * semnum = sem index
 */
void init_sem(int semid, int semnum, int init_value) {
	union semun semopts;
	semopts.val = init_value;
	
	semctl(semid, semnum, SETVAL, semopts);
}

/*
 * acquire an semafor in set
 */
int acquire_sem(int semid, int semnum){
	struct sembuf acquire = { semnum, -1, SEM_UNDO };
	semop(semid, &acquire, 1);

	return get_semafor_value(semid, semnum);

}

/*
 * release semafor in set
 */
int release_sem(int semid, int semnum){
	struct sembuf release = { semnum, +1, SEM_UNDO };
	semop(semid, &release, 1);

	return get_semafor_value(semid, semnum);

}

