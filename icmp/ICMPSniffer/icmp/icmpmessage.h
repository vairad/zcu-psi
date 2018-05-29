#ifndef ICMPMESSAGE_H
#define ICMPMESSAGE_H

#include <list>
#include <unistd.h>
#include <cstdint>
#include <string>

#include "icmp/icmpdefinitions.h"

class ICMPMessage
{
    uint8_t *data;
    size_t datalength;

    icmpHeader header;

public:
    ICMPMessage();
    icmpHeader getHeader();
    std::list<uint16_t> getPaddedData();
    void setContent(std::string strMessage);
    void setIdentifier(uint16_t identifier);
    void setSequenceNumber(uint16_t sequencer);
    void setType(uint8_t type);
};

#endif // ICMPMESSAGE_H
