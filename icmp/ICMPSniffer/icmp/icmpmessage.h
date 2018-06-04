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
    uint8_t *getData();
    size_t getDataLength();
    void setCode(uint8_t code);
    uint16_t getIdentifier();
    uint16_t getSequenceNumber();
    uint8_t getType();
    uint8_t getCode();
};

#endif // ICMPMESSAGE_H
