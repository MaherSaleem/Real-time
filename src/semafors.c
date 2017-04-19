#include <stdio.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <semaphore.h>

union semun {
	int val; /* Value for SETVAL */
	struct semid_ds *buf; /* Buffer for IPC_STAT, IPC_SET */
	int *array; /* Array for GETALL, SETALL */
	struct seminfo *__buf; /* Buffer for IPC_INFO
	 (Linux-specific) */
};

int get_semafor(int Key, int size){
	return semget(Key, size, IPC_CREAT | 0660);
}


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

int acquire_sem(int semid, int semnum){
	struct sembuf acquire = { semnum, -1, SEM_UNDO };
	semop(semid, &acquire, 1);

	return get_semafor_value(semid, semnum);

}
int release_sem(int semid, int semnum){
	struct sembuf release = { semnum, +1, SEM_UNDO };
	semop(semid, &release, 1);

	return get_semafor_value(semid, semnum);

}

