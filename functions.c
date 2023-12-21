#include "functions.h"

void print_error(char *message){
    write(STDERR_FILENO, message, strlen(message));
};

void gettftp(const char *host, const char *file){

};

void puttftp(){

};

// Construction of a Read Request (RRQ) packet
void rrq_request(char *request, const char *filename){
    // Opcode for RRQ is 1
    short opcode = htons(1);

    // Copy opcode to request buffer
    memcpy(request,&opcode,sizeof(short));

    // Copy filename to request buffer
    strcpy(request+sizeof (short),filename);

    // Copy mode
    strcpy(request+sizeof (short)+ strlen(filename)+1,"octet");
};

// Send a packet to the server
void send_packet(int socket_fd,const char *packet,size_t size,struct sockaddr *server_addr){
    sendto(socket_fd,packet,size,0,server_addr,sizeof *server_addr);
};

void receive_DAT(int socket_fd,struct sockaddr *server_addr){
    char buffer[516];

    // Receive the data packet
    ssize_t bytes_received = recvfrom(socket_fd,buffer,sizeof (buffer),0,server_addr,&(socklen_t){sizeof *server_addr});

    // Send ACK
    send_ACK(socket_fd,buffer[2],server_addr);
};

// Send ACK to the server
void send_ACK(int socket_fd, char block_number,struct sockaddr *server_addr){
    // Construction of ACK packet
    char ack_packet[4];
    memset(ack_packet,0,sizeof (ack_packet));

    // Opcode for ACK
    short opcode = htons(4);
    memcpy(ack_packet,&opcode,sizeof (short));

    // Copy block number to ACK packet
    ack_packet[2] = block_number;

    // Send ACK packet to the server
    sendto(socket_fd,ack_packet,sizeof (ack_packet),0,server_addr,sizeof *server_addr);
};

// Receive multiple Data (DAT) packets and their ACK
void receive_multiple_DAT(int socket_fd,struct sockaddr *server_addr){
    int block_number = 1;
    char buffer[516];

    while(1){
        // Receive data packet
        ssize_t bytes_received = recvfrom(socket_fd,buffer,sizeof (buffer),0,server_addr,&(socklen_t){sizeof *server_addr});

        // Send ACK for the current block number
        send_ACK(socket_fd,buffer[2],server_addr);
        block_number++;
    }
}