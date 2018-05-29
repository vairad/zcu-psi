#ifndef ICMPMESSAGE_H
#define ICMPMESSAGE_H

#include <list>
#include <unistd.h>
#include <cstdint>

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
};

#endif // ICMPMESSAGE_H
