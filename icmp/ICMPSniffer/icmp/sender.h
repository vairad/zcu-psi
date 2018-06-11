#ifndef SENDER_H
#define SENDER_H

#include "icmp/icmpmessage.h"

#include <string>
#include <thread>

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>

class Sender
{
    int sock_icmp;

    struct ether_header *eth_hdr;
    struct ip *ip_hdr_in, *ip_hdr_out;
    struct icmp *icmp_hdr_in, *icmp_hdr_out;

    static void run(Sender * object);
    void sendMessage(ICMPMessage &message);

    std::thread *sender;

public:
    Sender();
    ~Sender();

};

#endif // SENDER_H
