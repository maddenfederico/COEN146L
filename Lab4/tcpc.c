//Lab4: Client

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <errno.h>
#include <arpa/inet.h> 




int main (int argc, char *argv[]) {
    int		sockfd = 0, n = 0;
    char	buff[1024];
    struct	sockaddr_in servAddr; 

    if (argc != 3){
	    printf ("Usage: %s <port no>  <ip of server>\n",argv[0]);
	    exit (1);
    } 
    //Create socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("Failure to setup an endpoint socket");
        exit(1);
    } 

    //Set server address by filling sevAddr fields
    servAddr.sin_family = AF_INET;//your code
    servAddr.sin_port = htons(5460);//your code 
    struct hostent *host;//your code
    servAddr.sin_addr.s_addr = INADDR_ANY;//your code

    //Connet to server
    if (connect(sockfd, (struct sockaddr*) &servAddr, sizeof(struct sockaddr)) < 0){
		perror("Failure to connect to the srver");
        exit(1);
    } 
    //Open file
    printf("Creating file");
    int length;
    FILE* fp = fopen("file.txt", "w");
    printf("Receiving file");
    while((length = recv(sockfd, buff, 1024, 0)) > 0){
        fwrite(buff, 1, length, fp);
        fflush(fp);
    }
    printf("File recieved");
    fclose(fp);
    close (sockfd);
    return 0;
}
