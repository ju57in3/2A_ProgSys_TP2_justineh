#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

void print_error(char* message);
void gettftp();
void puttftp();
void rrq_request(char *request, const char *filename);
void send_packet(int socket_fd,const char *packet,size_t size,struct sockaddr *server_addr);
void send_ACK(int socket_fd, char block_number,struct sockaddr *server_addr);
void receive_multiple_DAT(int socket_fd,struct sockaddr *server_addr);