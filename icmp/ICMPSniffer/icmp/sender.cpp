#include "icmpmessage.h"
#include "icmputils.h"
#include "sender.h"
#include <iostream>


#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <string.h>



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

    uint8_t buf_outgoing[2048];
    size_t messageLen = sizeof(icmpHeader) + (message.getDataLength() * sizeof (uint8_t));

//    memset(dest source size);
    icmpHeader header = message.getHeader();
    header.checksum = 0;

    memcpy(buf_outgoing, &header, sizeof(icmpHeader));
    memcpy(buf_outgoing + sizeof(icmpHeader), message.getData(), message.getDataLength() * sizeof (uint8_t));

    header.checksum = ICMPUtils::computeCheckSum((uint16_t *)buf_outgoing, messageLen);
    memcpy(buf_outgoing, &header, sizeof(icmpHeader));


    sendto(sock_icmp, buf_outgoing, messageLen, 0, (struct sockaddr *) &dst, sizeof (dst));
}

Sender::~Sender()
{
    close(sock_icmp);
}
