#include "icmpmessage.h"
#include "sender.h"

#include <cstring>
#include <arpa/inet.h>

ICMPMessage::ICMPMessage()
{
    data = NULL;
    datalength = 0;
    header.codes = 0;
    header.gatewayInternetAddress = 0;
    destination = "";
    dst.sin_family = AF_INET;
    src.sin_family = AF_INET;
    source = "Local PC";
    destination = "Local PC";
}

ICMPMessage::ICMPMessage(icmpHeader header)
    : header(header)
{
    data = NULL;
    datalength = 0;
}

icmpHeader ICMPMessage::getHeader()
{
    return header;
}

std::list<uint16_t> ICMPMessage::getPaddedData()
{
    std::list<uint16_t> dataList;
    dataList.clear();

    for (size_t index = 0 ; index < datalength; ++index){
        uint16_t box = 0;
        uint8_t high = 0;
        uint8_t low = 0;

        if(index == datalength){
        high = data[index];
        }else{
        high = data[index];
        low = data[++index];
        }

        box += high;
        box = box << 8;
        box += low;
        dataList.push_back(box);
    }
    return dataList;
}

void ICMPMessage::setContent(std::string strMessage)
{
    if(data != NULL){
        delete data;
    }
    datalength = strMessage.length();
    data = new uint8_t[datalength];
    memset(data, 0 , sizeof(uint8_t) * datalength);

    for (size_t index = 0 ; index < datalength; ++index){
        uint8_t dataField = strMessage.at(index);
        data[index] = dataField;
    }
}

void ICMPMessage::setData(uint8_t *data, size_t dataLen)
{
    if(this->data != NULL){
        delete this->data;
    }
    this->datalength = dataLen;
    this->data = data;
}

void ICMPMessage::setIdentifier(uint16_t identifier)
{
    header.identifier = identifier;
}

void ICMPMessage::setSequenceNumber(uint16_t sequencer)
{
    header.sequenceNumber = sequencer;
}

void ICMPMessage::setType(uint8_t type)
{
    header.type = type;
}

void ICMPMessage::setCode(uint8_t code)
{
    header.code = code;
}

uint16_t ICMPMessage::getIdentifier()
{
   return header.identifier;
}

uint16_t ICMPMessage::getSequenceNumber()
{
    return header.sequenceNumber;
}

uint8_t ICMPMessage::getType()
{
   return header.type;
}

uint8_t ICMPMessage::getCode()
{
    return header.code;
}

std::string ICMPMessage::getSource()
{
    return source;
}

std::string ICMPMessage::getDestination()
{
    return destination;
}


void ICMPMessage::setSource(in_addr source)
{
    this->src.sin_addr = source;
    char buf[INET_ADDRSTRLEN];

    if (inet_ntop(AF_INET, &source, buf, sizeof(buf)) != NULL)
         printf("inet addr: %s\n", buf);
    else {
         perror("inet_ntop");
    }
    this->source = std::string(buf) ;
}

void ICMPMessage::setDestination(in_addr dest)
{
    this->dst.sin_addr = dest;
    char buf[INET_ADDRSTRLEN];

    if (inet_ntop(AF_INET, &dest, buf, sizeof(buf)) != NULL)
         printf("inet addr: %s\n", buf);
    else {
         perror("inet_ntop");
    }
    this->destination = std::string(buf) ;
}

sockaddr_in *ICMPMessage::getDst()
{
    return &dst;
}

sockaddr_in *ICMPMessage::getSrc()
{
    return &src;
}

void ICMPMessage::setDestination(std::string stringDest)
{
    dst.sin_family = AF_INET;
    dst.sin_addr = Sender::resolveHostname(stringDest.c_str());
    destination = stringDest;
}



uint8_t * ICMPMessage::getData(){
    return data;
}

size_t ICMPMessage::getDataLength(){
    return datalength;
}
