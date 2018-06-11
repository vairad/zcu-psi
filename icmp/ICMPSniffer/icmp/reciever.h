#ifndef RECIEVER_H
#define RECIEVER_H

#include <thread>

class Reciever
{
    int sock_eth;

    static void run(Reciever * object);

    std::thread *reciever;

public:
    Reciever();
    ~Reciever();
    void recieve();
};

#endif // RECIEVER_H
