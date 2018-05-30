#include "icmpmessage.h"

ICMPMessage::ICMPMessage()
{
    data = NULL;
    datalength = 0;
    header.codes = 0;
    header.gatewayInternetAddress = 0;
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

    for (size_t index = 0 ; index < datalength; ++index){
        uint8_t dataField = strMessage.at(index);
        data[index] = dataField;
    }
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

uint8_t * ICMPMessage::getData(){
    return data;
}

size_t ICMPMessage::getDataLength(){
    return datalength;
}
