#ifndef MESSAGEFACTORY_H
#define MESSAGEFACTORY_H

#include "icmpmessage.h"

#include <string>

class MessageFactory
{
    static uint16_t echoSequence;
public:
    static ICMPMessage * createEchoTest();
    static ICMPMessage * createEcho(std::string content);
};

#endif // MESSAGEFACTORY_H
