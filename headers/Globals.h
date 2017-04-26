
#include <stdio.h>
#include <stdlib.h>
#include "../headers/semafors.h"
#include "../headers/worker.h"
#include "../headers/setup_configrations.h"
#include "../headers/server_signals.h"
#include <unistd.h>

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

//=================GLOBAL VARIALBES SHARED FOR ALL FILES=======================



extern struct sockaddr_in serverAddr, clientAddr;
extern  socklen_t addr_size, client_addr_size;
extern int fd;
extern configs c;
extern int * process;
//=============================================================================



