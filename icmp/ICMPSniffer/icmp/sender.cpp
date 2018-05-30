#include "icmpmessage.h"
#include "sender.h"
#include <iostream>


#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>



Sender::Sender(std::string destination)
{
    int ret;
    int one = 1;

    this->destination = destination;

    dst.sin_family = AF_INET;
    dst.sin_addr.s_addr = inet_addr(destination.c_str());

    if ((sock_icmp = socket (AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0){
       std::cerr << "Socket problem";
       exit(1);
    }

//    if ((ret = setsockopt (sock_icmp, IPPROTO_IP, IP_HDRINCL, (char *) &one, sizeof (one))) < 0){
//       std::cerr << "Socket problem - setcockopt returned: " << ret;
//       exit(1);
//    }
}

void Sender::sendMessage(ICMPMessage &message){

    char buf_outgoing[2048];
    size_t messageLen;



    sendto(sock_icmp, "ahoj", 4, 0, (struct sockaddr *) &dst, sizeof (dst));
}

Sender::~Sender()
{
    close(sock_icmp);
}
