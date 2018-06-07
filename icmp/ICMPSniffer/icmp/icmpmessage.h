#ifndef ICMPMESSAGE_H
#define ICMPMESSAGE_H

#include <list>
#include <unistd.h>
#include <cstdint>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>

#include "icmp/icmpdefinitions.h"

class ICMPMessage
{
    uint8_t *data;
    size_t datalength;

    icmpHeader header;

    std::string destination;
    struct sockaddr_in dst;

    std::string source;
    struct sockaddr_in src;

public:
    ICMPMessage();
    ICMPMessage(icmpHeader header);
    icmpHeader getHeader();
    std::list<uint16_t> getPaddedData();
    void setContent(std::string strMessage);
    void setData(uint8_t *data, size_t dataLen);
    void setIdentifier(uint16_t identifier);
    void setSequenceNumber(uint16_t sequencer);
    void setType(uint8_t type);
    uint8_t *getData();
    size_t getDataLength();
    void setCode(uint8_t code);
    uint16_t getIdentifier();
    uint16_t getSequenceNumber();
    uint8_t getType();
    uint8_t getCode();
    void setSource(struct in_addr source);
    void setDestination(struct in_addr dest);
    struct sockaddr_in* getDst();
    struct sockaddr_in* getSrc();
    void setDestination(std::string stringDest);

    std::string getDestination();
    std::string getSource();

    void setTime1();
    void setTime2();
    void setTime3();
    void prepareTimeData();
};

#endif // ICMPMESSAGE_H
