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

uint16_t ICMPUtils::computeCheckSum(uint16_t *byteArray, size_t dataLen){
    int nleft = dataLen;
    int sum = 0;
    unsigned short *w = byteArray;
    unsigned short answer = 0;
    while (nleft > 1){
       sum += *w++;
       nleft -= 2;
    }
    if (nleft == 1){
       *(unsigned char *) (&answer) = *(unsigned char *) w;
       sum += answer;
    }
    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
    answer = ~sum;
    return (answer);
}
