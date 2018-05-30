#include "icmpmessage.h"
#include "icmputils.h"
#include "sender.h"
#include <iostream>

#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <string.h>
#include "errorcodes.h"



Sender::Sender(std::string destination)
{
    int ret;
    int one = 1;

    this->destination = destination;

    memset(&dst, 0, sizeof dst);

    dst.sin_family = AF_INET;
    dst.sin_addr = resolveHostname(destination.c_str());

    if ((sock_icmp = socket (AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0){
       std::cerr << "Socket problem";
       exit(SOCKET_ERROR);
    }

//    if ((ret = setsockopt (sock_icmp, IPPROTO_IP, IP_HDRINCL, (char *) &one, sizeof (one))) < 0){
//       std::cerr << "Socket problem - setcockopt returned: " << ret;
//       exit(1);
//    }
}

struct in_addr Sender::resolveHostname(std::string hostname){
    struct hostent *hp = gethostbyname(hostname.c_str());
    struct in_addr addr;
    if (hp == NULL) {
       std::cerr << "Couldn't resolve hostname.";
       exit(HOSTNAME_ERROR);
    } else {
       if ( hp -> h_addr_list[0] != NULL) {
          addr = *((struct in_addr*)( hp -> h_addr_list[0]));
       }
    }
    return addr;
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
