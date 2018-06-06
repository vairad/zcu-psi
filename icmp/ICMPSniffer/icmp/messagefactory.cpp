#include "messagefactory.h"


uint16_t MessageFactory::echoSequence = 0;

ICMPMessage *MessageFactory::createEchoTest()
{
    return createEcho("TEST");
}

ICMPMessage *MessageFactory::createEcho(std::string content)
{
    ICMPMessage *message = new ICMPMessage();
    message->setType(icmpMessageType::Echo);
    message->setContent(content);
    message->setIdentifier(1); // todo map host to identifier ... sequence
    message->setSequenceNumber(echoSequence++);
    message->setDestination("localhost");
    return message;
}
