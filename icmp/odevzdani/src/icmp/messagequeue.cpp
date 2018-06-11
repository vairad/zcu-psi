#include "icmp/messagequeue.h"

#include <iostream>

MessageQueue::MessageQueue()
{
    messageCount = 0;
}

bool MessageQueue::push_msg(ICMPMessage *msg){
    std::unique_lock<decltype(queue_lock)> lock(queue_lock);
    try
    {
        message_queue.push(msg);
    } catch (std::exception &e){
         std::cerr << "Výjimka při vkládání do fronty zpráv" <<  e.what();
         return false;
    }

    messageCount++;
    condition.notify_one();
    return true;
}

ICMPMessage *MessageQueue::pop_msg(void)
{
    std::unique_lock<decltype(queue_lock)> lock(queue_lock);

    while(!messageCount){
        condition.wait(lock);
    }
    ICMPMessage *msg = message_queue.front();
    message_queue.pop();
    --messageCount;
    return msg;
}
