// SCU COEN 146
//
// This program implements the client side of stop & wait protocol
// the client transfers a file to the server
//
//
// For the stop and wait protocolL, the assumptions are:
//      -- packet corruption, and packet loss


#include	"tfv1.h"

// global variables
int state = 0; // only two states: 0 and 1
int sock;
struct sockaddr_in serverAddr;

socklen_t addr_size;



// list of functions
int main (int, char *[]);

// to reliably send a chunk of data
void my_send (char *, int);

// part of the my_send() function
void recv_ack (PACKET *, int);

// computes checksum using XOR of bytes
int calc_checksum (char *, int);




int main (int argc, char *argv[])
{
    char	buff[SIZE];
    FILE	*fp; // file to be sent to the server
    int		r;
    
    if (argc != 5)
    {
        printf ("usage:usage: ./client port IP source_file dest_file\n");
        return 1;
    }
    
    
    // configure address
    memset (&serverAddr, '0', sizeof (serverAddr));
	serverAddr.sin_family = AF_INET; //setup server address struct
	serverAddr.sin_port =  htons(atoi(argv[1])); //port
    serverAddr.sin_addr.s_addr = inet_addr(argv[2]); //server address
    addr_size = sizeof(serverAddr); //address size
    
    // create UDP socket
    if ((sock = socket (PF_INET, SOCK_DGRAM, 0)) < 0)
    {
        printf ("socket error\n");
        return 1;
    }
    printf ("UDP socket has been created!\n");
    
    if ((fp = fopen (argv[3], "rb")) == NULL)
    {
        printf ("fopen error\n");
        return 1;
    }
    printf ("Source file opened successfully!\n");

    
    printf ("Sending file name...");
	my_send(argv[4], strlen(argv[4]) + 1); //send filename
	
    printf ("Done!\n");

    
    printf ("Now sending source file contents...");
	while((r = fread(buff, sizeof(char), SIZE, fp)) > 0) //read file contents
	{
		my_send(buff, r); //transmit file contents to server
	}

    printf ("Done!\n");
    
    
    // After transmitting the file, a packet with no data (len = 0) is sent to
    // notify the receiver that the file transfer has completed
    printf ("Informing the server about the completion of file transmission...\n");
    
	my_send("", 0); //tell server done transmitting
    printf ("Done!\n");
    
    
    fclose (fp);
    close (sock);
    
    return 0;
    
}


//***********************
// sends data (of size nbbytes) reliably to the sender
// **********************
void my_send (char *data, int nbytes)
{
    PACKET	buf;
    int		r;
    
    memcpy(buf.data, data, nbytes); //copy file contents to packet
	buf.header.len = nbytes; //setup packet vars
	buf.header.seq_ack = state;
    
    //default checksum value is 0
    buf.header.checksum = 0;
    
    
    // simulating erroneous channel... corruption and loss
    // the probability of correct checksum is 80%
    r = rand () % 10;
    if (r <= 8)
        buf.header.checksum = calc_checksum ((char *)&buf, sizeof(HEADER) + nbytes); //calculate chksum
    else
        printf ("Packet got corrupted on the way!\n"); //otherwise pckt corrupt
    
    
    // the probability of no packet loss is 80%
    r = rand () % 10;
    if (r <= 8)
		sendto(sock, &buf, sizeof(HEADER) + nbytes,0, (struct sockaddr *) &serverAddr, addr_size); //transmit packet
    else
		printf ("Packet lost!\n"); //otherwise packet lost
    
    // wait for ack
	recv_ack(&buf, nbytes); //receive ACK
    
    return;
}



//***********************
// wait for ack
// **********************
void recv_ack (PACKET *buf, int nbytes)
{
    HEADER	receive_buf;
    int		cs;
    int		r;
    struct timeval tv;
    int		rv;
    int		counter = 0;
    
    // The fd_set data type represents file descriptor sets for the select function
    // It is actually a bit array
    // (set of socket descriptors)
    fd_set readfds;
    
    fcntl(sock, F_SETFL, O_NONBLOCK);
    
    while (1)
    {
        while (1)
        {
            FD_ZERO (&readfds); // Clear an fd_set
            
            // void FD_SET (int filedes, fd_set *set)
            // This macro adds filedes to the file descriptor set set.
            FD_SET (sock, &readfds);
            
            tv.tv_sec = 5;
            tv.tv_usec = 0;
            
            
            // int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
            // maxfd: maximum number of descriptor ready.
            // timeout: How long to wait for select to return.
            //The select function blocks , till an activity occurs
            
            // On success, select() and pselect() return the number of file
            // descriptors contained in the three returned descriptor sets (that is,
            // the total number of bits that are set in readfds, writefds,
            // exceptfds) which may be zero if the timeout expires before anything
            // interesting happens
            
            // in the following we only pass readfds because we are interested in reading only
            rv = select (sock + 1, &readfds, NULL, NULL, &tv);
            
            
            // return value is 1 when there is a bit set in readfds
            // so there is data to be read
            if (rv == 1)
            {
				break; //if ACK received, break from inner loop
            }
            
            // this means select() returned due to timeout event
            else if (rv == 0)
            {
                printf ("timeout\n"); //timeout if ACK not received
                if (nbytes == 0)
                {
                    printf("increment counter\n"); //increment counter for final message
                    counter++;
                    if (counter == 3) //if 3 RTTs, terminate the program
                        return;
                }
                // resend packet
                //default checksum value is 0
                buf->header.len = nbytes; //setup packet vars
                buf->header.seq_ack = state;
                buf->header.checksum = 0;
                
                // simulating erroneous channel... corruption and loss
                // the probability of correct checksum is 80%
                r = rand () % 10;
                if (r <= 8)
                    buf->header.checksum = calc_checksum ((char *)buf, sizeof (HEADER) + nbytes); //calc chksum
                else
                    printf ("Packet got corrupted on the way!\n"); //otherwise pckt corrupted
                
                // the probability of no packet loss is 80%
                r = rand () % 10;
                if (r <= 8)
                {
                    sendto(sock, buf, sizeof(HEADER) + nbytes, 0, (struct sockaddr *) &serverAddr, addr_size); //transmit pckt
                }
                else
                    printf ("Packet lost!\n"); //otherwise pckt lost
            }
        }
        
        
        
        // we break the previous while(1) loop when there is data to be read (ack received)
        
        recvfrom (sock, &receive_buf, sizeof(HEADER), 0, NULL, NULL); //receive the ACK
        
        cs = receive_buf.checksum; //save chksum
        receive_buf.checksum = 0;
        
        
        // recalculate checksum of the received ack packet
        if ((calc_checksum ((char *)&receive_buf, sizeof (HEADER)) != cs) || (receive_buf.seq_ack != state)) //if bad ack: wrong chksum or seq num
        {
            // a bad ack has been received
            printf("Bad ACK!\n");

            // resend packet
            //default checksum value is 0
            buf->header.len = nbytes;
            buf->header.seq_ack = state;
            buf->header.checksum = 0;
            
            // simulating erroneous channel... corruption and loss
            // the probability of correct checksum is 80%
            r = rand () % 10;
            if (r <= 8)
                buf->header.checksum = calc_checksum ((char *)buf, sizeof (HEADER) + nbytes); //calc chksum
            else
                printf ("Packet got corrupted on the way!\n"); //otherwise pckt corrupted
            
            // the probability of no packet loss is 80%
            r = rand () % 10;
            if (r <= 8)
            {
                sendto(sock, buf, sizeof(HEADER) + nbytes, 0, (struct sockaddr *) &serverAddr, addr_size); //transmit pckt
            }
            else
                printf ("Packet lost!\n"); //otherwise pckt lost
        }

        else
        {
            printf("Good ACK!\n"); //if good ack:
    		state = !state; //toggle state 
			return;
        }
		
    }
}



//***********************
// calculate checksum by using XOR
// **********************
int calc_checksum (char *buf, int tbytes)
{
    int		i;
    char	cs = 0;
    char 	*p;

	p = buf;
    cs = *p++;
	for (i=1; i<tbytes; i++, p++) //loop through buf and xor bytes
	{
		cs ^= *p;
	}
    return (int)cs;
}





