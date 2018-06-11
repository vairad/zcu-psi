#include "icmp/icmpmessage.h"
#include "icmp/utils.h"

#include <cstring>
#include <iostream>
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
    source = "ICMP Generator";
    destination = "ICMP Generator";
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
    header.identifier = htons(identifier);
}

void ICMPMessage::setSequenceNumber(uint16_t sequencer)
{
    header.sequenceNumber = htons(sequencer);
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
   return ntohs(header.identifier);
}

uint16_t ICMPMessage::getSequenceNumber()
{
    return ntohs(header.sequenceNumber);
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
         std::cout << "Rewrite in_addr to " << buf << std::endl;
    else {
         std::cerr << "Could not rewrite in_addr" << std::endl;
    }
    this->source = std::string(buf) ;
}

void ICMPMessage::setDestination(in_addr dest)
{
    this->dst.sin_addr = dest;
    char buf[INET_ADDRSTRLEN];

    if (inet_ntop(AF_INET, &dest, buf, sizeof(buf)) != NULL)
         std::cout << "Rewrite in_addr to " << buf << std::endl;
    else {
         std::cerr << "Could not rewrite in_addr" << std::endl;
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

void ICMPMessage::prepareTimeData(){
    if(data){
        delete data;
    }
    datalength = 3 * sizeof(uint32_t);
    data = new uint8_t[datalength];
    memset(data, 0, datalength);
}

void ICMPMessage::setDestination(std::string stringDest)
{
    dst.sin_family = AF_INET;

    if(stringDest.length() == 0){
        memset(&dst, 0, sizeof(dst));
    }else{
        dst.sin_addr = Utils::resolveHostname(stringDest.c_str());
    }
    destination = stringDest;
}

void ICMPMessage::setTime1()
{
    if(datalength == 3*4){
        uint32_t * times = (uint32_t *)data;
        times[0] = htonl(Utils::milisFromMidnight());
    }
}

void ICMPMessage::setTime2()
{
    if(datalength == 3*4){
        uint32_t * times = (uint32_t *)data;
        times[1] = htonl(Utils::milisFromMidnight());
    }
}

void ICMPMessage::setTime3()
{
    if(datalength == 3*4){
        uint32_t * times = (uint32_t *)data;
        times[2] = htonl(Utils::milisFromMidnight());
    }
}

uint8_t * ICMPMessage::getData(){
    return data;
}

size_t ICMPMessage::getDataLength(){
    return datalength;
}
