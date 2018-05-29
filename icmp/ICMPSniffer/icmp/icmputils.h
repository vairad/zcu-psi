#ifndef ICMPUTILS_H
#define ICMPUTILS_H

#include <cstdint>
#include "icmp/icmpmessage.h"

class ICMPUtils
{
public:
static uint16_t computeCheckSum(ICMPMessage &message);
};

#endif // ICMPUTILS_H
