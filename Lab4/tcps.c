 //Lab4: Concurrent server  

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/types.h>
#include <pthread.h>

#define CONN 10 // 10 connections


struct d { 		//structure to hold thread data
   int con; //connection
   int fP; //file pointer
   int tID; //thread id
};

int main (int argc, char *argv[]){
    if (argc != 3){
		  printf ("Usage: %s <port number> <src_file> \n",argv[0]);
		  exit(1);
	  }
    int		sockfd;             //Declare socket file descriptor
    char	buff[1024];           //Declare a buffer of size 1k bytes
    FILE*  fp;
    int connfd;    // connection descriptor
    
    //Declare server address to which to bind for receiving messages and client address to fill in sending address
    struct	sockaddr_in servAddr, clienAddr; 
    
    //Set server address/ port
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl (INADDR_ANY);
    servAddr.sin_port = htons (atoi (argv[1])); 
    
    //Open a TCP socket, if successful, returns a descriptor
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ){
      perror("Failure to setup an endpoint socket");
      exit(1);
    }
    
    //Set address/port of server endpoint for socket descriptor
    if ((bind(sockfd, (struct sockaddr*)& servAddr, sizeof(struct sockaddr))) < 0){
      perror("Failure to bind server address to the endpoint socket");
      exit(1);
    } 

    // Server listening to the socket endpoint, and can queue 10 client requests
    //your code 
    listen(sockfd, CONN);

    printf ("opening file %s\n", argv[2]);
    if ((fp = fopen(argv[2], "r")) < 0){
      perror("Failure to open the file");
      exit(1);
    } 
    int sin_size = sizeof(struct sockaddr_in); //size of sockaddr_in
    
    //Server loops all the time accepting conncections when they are made
    while (1) {
        //Server accepting to establish a connection with a connecting client, if successful, returns a connection descriptor
        if ((connfd = accept(sockfd, (struct sockaddr*)& clienAddr, (socklen_t*) &sin_size)) < 0){
          perror("Failure to accept connection to the client");
          exit(1);
        }
        //Connection established, server begins to read and write to the connecting client
        printf("Connection Established with client: IP %s and Port %d\n", inet_ntoa(clienAddr.sin_addr), ntohs(clienAddr.sin_port));
        sleep(1);
        char buff[1024];
        int num_bytes;
        printf("Sending file\n");
        while(!feof(fp)){
          num_bytes = fread(buff, 1, 1024, fp);
          sendto(connfd, buff, num_bytes, 0, (struct sockaddr *)&servAddr, sizeof(struct sockaddr));
        }
        printf("Sent file\n");
    }
    fclose(fp);
    close(sockfd);
    return 0;
}
