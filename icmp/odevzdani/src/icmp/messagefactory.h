#ifndef MESSAGEFACTORY_H
#define MESSAGEFACTORY_H

#include "icmp/icmpmessage.h"

#include <string>

class MessageFactory
{
    static uint16_t echoSequence;
public:
    static ICMPMessage * createEchoTest(std::string hostname = "");
    static ICMPMessage * createEcho(std::string content, std::string hostname = "");
};

#endif // MESSAGEFACTORY_H
