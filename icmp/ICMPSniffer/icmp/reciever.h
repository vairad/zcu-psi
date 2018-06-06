#ifndef RECIEVER_H
#define RECIEVER_H


class Reciever
{
    int sock_eth;

    static void reciever(Reciever * object);
public:
    Reciever();
    ~Reciever();
    void recieve();
};

#endif // RECIEVER_H
