#ifndef ICMPUTILS_H
#define ICMPUTILS_H

#include "icmp/icmpmessage.h"

#include <cstdint>

class ICMPUtils
{
public:
    static uint16_t computeCheckSum(ICMPMessage &message);
    static uint16_t computeCheckSum(uint16_t *byteArray, size_t dataLen);
};

#endif // ICMPUTILS_H
