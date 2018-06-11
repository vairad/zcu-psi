#include "reciever.h"
#include "errorcodes.h"
#include "icmp/icmpdefinitions.h"
#include "icmp/icmpmessage.h"
#include "gui/guiinterface.h"
#include "icmp/messenger.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <net/ethernet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <netinet/ip_icmp.h>
#include <netinet/ether.h>
#include <iostream>

#include <QDebug>

void Reciever::run(Reciever *object)
{
    while(Messenger::recieve()){
        object->recieve();
    }
    std::cout << "Reciever thread end."  << std::endl;
}

Reciever::Reciever()
{
    if((sock_eth = socket(AF_INET , SOCK_RAW , IPPROTO_ICMP)) < 0){
        std::cerr << "Socket error"  << std::endl;
         exit (ETH_SOCKET_ERROR);
    }

    struct timeval tv;
    tv.tv_sec = 2;
    tv.tv_usec = 0;
    if(setsockopt(sock_eth, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv) < 0){
        std::cerr << "Socket timeout oprtion error" << std::endl;
        exit (ETH_SOCKET_ERROR);
    }

    reciever = new std::thread(run, this);
}

Reciever::~Reciever()
{
   reciever->join();
   delete reciever;
   close(sock_eth);
   std::cout << "Reciever deleted" << std::endl;
}

void Reciever::recieve()
{
   uint8_t buf_incoming[1500];
   struct ip *ip_hdr_in = (struct ip *) (buf_incoming);
   memset(buf_incoming, 0, sizeof(buf_incoming));

   size_t ret = recv(sock_eth, buf_incoming, sizeof (buf_incoming), 0);
   if(ret == -1){
       return;
   }
   size_t dataLen = ret - (sizeof(struct ip) + sizeof( struct icmpHeader));
   if(dataLen > 0){
       std::string msg = "Recieved " + std::to_string(ret) +"bytes with " + std::to_string(dataLen) + "bytes of data.";
       std::cout << msg.c_str()  << std::endl;

       struct icmpHeader *header = new icmpHeader() ;
       memcpy(header, buf_incoming + sizeof (struct ip) , sizeof(struct icmpHeader));

       qDebug() << "Create message";
       ICMPMessage *message = new ICMPMessage(*header);
       uint8_t *data = new uint8_t[dataLen];
       memcpy(data, buf_incoming + (ret - dataLen) , dataLen);
       message->setData(data, dataLen);

       message->setSource(ip_hdr_in->ip_src);
       message->setDestination(ip_hdr_in->ip_dst);

       qDebug() << "Add message to GUI";
       GuiInterface::addMessage(*message);
    }
}


