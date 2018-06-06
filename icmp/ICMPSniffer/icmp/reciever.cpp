#include "reciever.h"
#include "errorcodes.h"
#include "icmpdefinitions.h"
#include "icmpmessage.h"
#include "gui/guiinterface.h"
#include "icmp/messenger.h"

#include <stdio.h>
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

void Reciever::reciever(Reciever *object)
{
    while(Messenger::recieve()){
        object->recieve();
    }
}

Reciever::Reciever()
{
//    if ((sock_eth = socket (AF_INET, SOCK_PACKET, htons (ETH_P_ALL))) < 0)
//    {
//       std::cerr << "Socket error";
//       exit (ETH_SOCKET_ERROR);
//    }
    if((sock_eth = socket(AF_INET , SOCK_RAW , IPPROTO_ICMP)) < 0){
        std::cerr << "Socket error";
         exit (ETH_SOCKET_ERROR);
    }

    std::thread thread(reciever, this);
    thread.detach();
}

Reciever::~Reciever()
{
   close(sock_eth);
}

void Reciever::recieve()
{
   uint8_t buf_incoming[1500];
   struct ip *ip_hdr_in = (struct ip *) (buf_incoming);
   memset(buf_incoming, 0, sizeof(buf_incoming));

   size_t ret = recv(sock_eth, buf_incoming, sizeof (buf_incoming), 0);
   size_t dataLen = ret - (sizeof(struct ip) + sizeof( struct icmpHeader));
   if(dataLen > 0){
       std::string msg = "Recieved " + std::to_string(ret) +"bytes with " + std::to_string(dataLen) + "bytes of data.";
       qDebug() << msg.c_str();

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


