#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H


#include "icmp/icmpmessage.h"
#include "icmp/messagequeue.h"

#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>

class MessageQueue
{
    std::mutex queue_lock;
    std::queue<ICMPMessage *> message_queue;
    std::condition_variable condition;
    size_t messageCount;

public:
    MessageQueue();
    ICMPMessage *pop_msg();
    bool push_msg(ICMPMessage *msg);
};



#endif // MESSAGEQUEUE_H
