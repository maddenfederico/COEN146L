//Lab5 Client
#include "lab5.h"

/*The simplest checksum algorithm is the so-called longitudinal parity check, 
which breaks the data into "bytes" with a fixed number 8 of bits, and then 
computes the exclusive or (XOR) of all those bytes. 
The result is appended to the message as an extra byte*/
//getChecksum()
int getChecksum(Packet packet) {
    packet.header.cksum = 0;
    int checksum = 0;
    char *ptr = (char *)&packet;
    char *end = ptr + sizeof(Header) + packet.header.len;
    while (ptr < end) {
        checksum ^= *ptr++;
    } 
        return checksum;
}
// printPacket()
void printPacket(Packet packet) {
    printf("Packet{ header: { seq_ack: %d, len: %d, cksum: %d }, data: \"",
            packet.header.seq_ack,
            packet.header.len,
            packet.header.cksum);
    fwrite(packet.data, (size_t)packet.header.len, 1, stdout);
    printf("\" }\n");
}
//clientSend()
void clientSend(int sockfd, const struct sockaddr *address, socklen_t addrlen, Packet packet) {
    while (1) {	
		packet.header.cksum=getChecksum(packet);
        // send the packet
        printf("Client sending packet\n");
	    //your code to send packet
        sendto (sockfd, &packet, sizeof(packet), 0, address, addrlen);
        // receive an Ack from the server
        Packet recvpacket;
	    //your code to receive packet/Ack
        recvfrom(sockfd, &recvpacket, sizeof(recvpacket), 0, address, &addrlen);

        // print what was received
        printf("Client received ACK %d, checksum %d - \n", recvpacket.header.seq_ack, recvpacket.header.cksum);
        // your code to validate the ACK
        
        if (recvpacket.header.cksum != getChecksum(recvpacket)) {
            // bad checksum, resend packet
            printf("Client: Bad checksum, expected checksum was: %d\n", getChecksum(recvpacket));
        } else if (recvpacket.header.seq_ack!=packet.header.seq_ack) {
            // incorrect sequence number, resend packet
            printf("Client: Bad seqnum, expected sequence number was: %d\n",packet.header.seq_ack);
	    
        } else {
            // good ACK, we're done
            printf("Client: Good ACK\n");
            break;
        }
    }
}

int main(int argc, char *argv[]) {
    // check arguments
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <ip> <port> <infile>\n", argv[0]);
        return 1;
    }

    // your code to create and configure the socket [name the socket sockfd] 
    int sockfd;
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
	    perror("Failed to setup endpoint socket.\n");
	    exit(1);	
    }

    // your code to initialize server address structure using argv[2] and argv[1]
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));

    socklen_t addr_length = sizeof(addr);
    struct hostent* host = (struct hostent*) gethostbyname(argv[1]);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[2]));
    addr.sin_addr = *((struct in_addr*) host->h_addr_list[0]);
    
    
    int fp;
    // your code to open file using argv[3]
    if((fp = open(argv[3], O_RDONLY)) < 0){
    	perror("Failed to open file\n");
	    exit(1);
    }

    // your code to send file contents to server
    int seq=0;
    Packet pack;
    int bytes;
    while((bytes = read(fp, pack.data, sizeof(pack.data))) > 0){
    	pack.header.seq_ack=seq;
    	pack.header.len=bytes;
        if(rand() % 20 < 5){
            pack.header.cksum=0;
        }else
    	    pack.header.cksum=getChecksum(pack);
    	clientSend(sockfd, &addr, addr_length, pack);
        memset(&pack, 0, sizeof(pack));
    	seq=(seq+1)%2;
    }

    // send zero-length packet to server to end connection
    Packet final;
    final.header.seq_ack=seq;
    final.header.len=0;
    final.header.cksum=getChecksum(final);
    clientSend(sockfd,(struct sockaddr *)&addr, addr_length, final);
    // clean up
	//-close the sockets and file
    close(fp);
    close(sockfd);
    return 0;
}
