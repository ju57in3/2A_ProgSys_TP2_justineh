#include "functions.h"

#define INVALID_NUMBER_ARGUMENTS "Invalid number of arguments"
#define ERROR_GETADDRINFO "Client : Error 'Getaddrinfo'"
#define ERROR_SOCKET "Error creating socket"

int main(int argc, char *argv[]) {
    struct addrinfo hints;
    struct addrinfo *serverinfo;
    int status;
    int socket_fd = socket(serverinfo->ai_family,serverinfo->ai_socktype,serverinfo->ai_protocol);

    // Checking number of arguments
    if (argc != 3){
        print_error(INVALID_NUMBER_ARGUMENTS);
        exit(EXIT_FAILURE);
    }

    // Determination of the first command-line argument
    if(strcmp(argv[1],"gettftp")==0){
        gettftp(argv[2],argv[3]);
    }
    if(strcmp(argv[1],"puttftp")==0){
        puttftp(argv[2],argv[3]);
    }

    // Adress information setup
    memset(&hints,0,sizeof hints);
    hints.ai_family =AF_UNSPEC; // AF_INET pour IPv4
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = IPPROTO_UDP;

    // Getting the server address
    if((status = getaddrinfo(argv[2], "69",&hints,&serverinfo)) != 0){
        print_error(ERROR_GETADDRINFO);
        exit(EXIT_FAILURE);
    }

    // Checking the socket création
    if(socket_fd == -1){
        print_error(ERROR_SOCKET);
        exit(EXIT_FAILURE);
    }

    char request[512];
    rrq_request(request,argv[3]);

    // Send the RRQ request to the server
    send_packet(socket_fd,request,sizeof (short)+ strlen(argv[3])+1+ strlen("octet")+1,serverinfo->ai_addr);
    freeaddrinfo(serverinfo);
    close(socket_fd);
}
