#ifndef MESSENGER_H
#define MESSENGER_H

#include "messagequeue.h"

class Messenger
{
   static MessageQueue sendQueue;
   static MessageQueue recieveQueue;
   static bool sendFlag;
   static bool recieveFlag;
public:
   static MessageQueue & getToSend();
   static MessageQueue & getRecieved();
   static bool send();
   static bool recieve();
   static void stopMessaging();
};

#endif // MESSENGER_H
