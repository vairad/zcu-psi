#include "messagefactory.h"


uint16_t MessageFactory::echoSequence = 0;

ICMPMessage *MessageFactory::createEchoTest(std::string hostname)
{
    return createEcho("TEST", hostname);
}

ICMPMessage *MessageFactory::createEcho(std::string content, std::string hostname)
{
    ICMPMessage *message = new ICMPMessage();
    message->setType(icmpMessageType::Echo);
    message->setContent(content);
    message->setIdentifier(1); // todo map host to identifier ... sequence
    message->setSequenceNumber(echoSequence++);
    if(hostname.empty()){
           message->setDestination("localhost");
    }else{
           message->setDestination(hostname);
    }

    return message;
}
