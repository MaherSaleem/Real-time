/************* TCP CLIENT CODE *******************/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(){

  int fd, portNum, nBytes2;
  char buffer[1024];
  struct sockaddr_in serverAddr;
  socklen_t addr_size;

  /*Create TCP socket*/
  fd = socket(AF_INET, SOCK_STREAM, 0);

  /*Configure settings in address struct*/
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(7245);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

  /*Initialize size variable to be used later on*/
  addr_size = sizeof(serverAddr);

 

  
  // connect to server
  if(connect(fd, (struct sockaddr*) &serverAddr, sizeof(serverAddr)) < 0) {
    perror("connect\n"); 
    exit(1);
  }

  //waiting for user to Enter GET requets
  printf(">>");
  fgets(buffer,1024,stdin);


  nBytes2 = strlen(buffer) + 1;

  int nbytes;
  /*Send the GET message from server*/
  if((nbytes = write(fd, buffer, nBytes2)) < 0) {
    perror("write\n");
    exit(1);
  }

  while((nbytes = read(fd, &buffer, sizeof(buffer))) > 0){
    printf("%s", buffer);

  }



  return 0;
}
