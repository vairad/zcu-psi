#include "icmp/messenger.h"

bool Messenger::sendFlag = true;
bool Messenger::recieveFlag = true;

MessageQueue Messenger::sendQueue;

MessageQueue Messenger::recieveQueue;

MessageQueue &Messenger::getToSend()
{
    return sendQueue;
}

MessageQueue &Messenger::getRecieved()
{
    return recieveQueue;
}

bool Messenger::send()
{
    return sendFlag;
}

bool Messenger::recieve()
{
    return recieveFlag;
}

void Messenger::stopMessaging()
{
    sendFlag = false;
    recieveFlag = false;
    sendQueue.push_msg(new ICMPMessage());
}
