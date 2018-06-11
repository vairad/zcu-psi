#include "icmp/icmpmessage.h"
#include "icmp/icmputils.h"
#include "icmp/sender.h"
#include "icmp/messenger.h"
#include <iostream>

#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <string.h>

#include "gui/guiinterface.h"
#include "errorcodes.h"
#include "exceptions.h"

#include <thread>
#include <QDebug>

void Sender::run(Sender *object)
{
    while (Messenger::send()) {
        qDebug() << "Before lock";
        ICMPMessage * msgPtr = Messenger::getToSend().pop_msg();
        qDebug() << "Message readed";
        ICMPMessage msg = *msgPtr;
        object->sendMessage(msg);
    }
    std::cout << "Sender thread end.";
}

Sender::Sender()
{
    if ((sock_icmp = socket (AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0){
       std::cerr << "Socket problem";
       exit(SOCKET_ERROR);
    }
    sender = new std::thread(run, (Sender *)this);
}


void Sender::sendMessage(ICMPMessage &message){
    std::cout << "SendMessage";
    uint8_t buf_outgoing[2048];
    size_t messageLen = sizeof(icmpHeader) + (message.getDataLength() * sizeof (uint8_t));

    icmpHeader header = message.getHeader();
    header.checksum = 0;

    memcpy(buf_outgoing, &header, sizeof(icmpHeader));
    memcpy(buf_outgoing + sizeof(icmpHeader), message.getData(), message.getDataLength() * sizeof (uint8_t));

    header.checksum = ICMPUtils::computeCheckSum((uint16_t *)buf_outgoing, messageLen);
    memcpy(buf_outgoing, &header, sizeof(icmpHeader));

    size_t result = sendto(sock_icmp, buf_outgoing, messageLen, 0, (struct sockaddr *) message.getDst(), sizeof (struct sockaddr_in));

    std::string debugMsg = "sended: ";
    debugMsg += std::to_string(result);
    debugMsg += "bytes";
    std::cout << debugMsg;

    if(result > 0){
            GuiInterface::addMessage(message);
    }
}

Sender::~Sender()
{
    sender->join();
    delete sender;
    close(sock_icmp);
    std::cout << "Sender deleted";
}
