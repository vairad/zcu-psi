#include "icmputils.h"

#include <list>


/// ///////////////////////////////////////////////////////////////////
/// Method computes ICMPv4 checksum.
///
/// The checksum is the 16-bit ones’s complement of the one’s
/// complement sum of the ICMP message starting with the ICMP Type.
/// For computing the checksum , the checksum field should be zero.
/// If the total length is odd, the received data is padded with one
/// octet of zeros for computing the checksum.
///
/// \brief ICMPUtils::computeCheckSum
/// \param message object of ICMPMessage
/// \return computed checsum
///
uint16_t ICMPUtils::computeCheckSum(ICMPMessage &message)
{
    icmpHeader header = message.getHeader();
    uint16_t sum = 0;

    sum += header.codes;
    sum += header.identifier;
    sum += header.sequenceNumber;

    std::list<uint16_t> data =  message.getPaddedData();
    for (auto const& i : data) {
        sum += i;
    }

    return ~sum;
}
