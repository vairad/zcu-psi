#ifndef ICMPDEFINITIONS_H
#define ICMPDEFINITIONS_H

#include <cstdint>

enum icmpMessageType{
    EchoReply = 0,
    DestinationUnreachable = 3,
    SourceQuench = 4,
    Redirect = 5,
    Echo = 8,
    Time_Exceeded = 11,
    Parameter_Problem = 12,
    Timestamp = 13,
    Timestamp_Reply = 14,
    Information_Request = 15,
    Information_Reply = 16
};


enum icmpMessageCode{
    net_unreachable = 0,
    host_unreachable = 1,
    rotocol_unreachable = 2,
    port_unreachable = 3,
    fragmentation_needed = 4,
    DF_set = 4,
    source_route_failed = 5,
    ttl_exceeded = 0,
    fragment_reassembly_time_exceeded = 1,
    pointer_indicate_error = 0
};

enum icmpRedirectCodes{
    forNetwork = 0,
    forHost = 1,
    forToSAndNetwork = 2,
    forToSAndHost = 3
};

struct icmpHeader {
    struct {
        union {
            uint16_t codes;
            struct {
                uint8_t type; //high
                uint8_t code; //low
            };
        };
        uint16_t checksum;
    };
    union {
        struct{
            uint8_t pointer;
        };
        uint32_t gatewayInternetAddress;
        struct{
            uint16_t identifier; //high
            uint16_t sequenceNumber; //low
        };
    };
}
;



#endif // ICMPDEFINITIONS_H
