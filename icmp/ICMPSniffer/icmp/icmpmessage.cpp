#include "icmpmessage.h"

ICMPMessage::ICMPMessage()
{

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
