#ifndef SENDER_H
#define SENDER_H

#include "icmp/icmpmessage.h"

#include <string>

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>

class Sender
{
    int sock_icmp;
    std::string destination;

    struct sockaddr_in dst;

    struct ether_header *eth_hdr;
    struct ip *ip_hdr_in, *ip_hdr_out;
    struct icmp *icmp_hdr_in, *icmp_hdr_out;

public:
    Sender(std::string destination);
    void sendMessage(ICMPMessage &message);
    ~Sender();
    in_addr resolveHostname(std::string hostname);
};

#endif // SENDER_H
