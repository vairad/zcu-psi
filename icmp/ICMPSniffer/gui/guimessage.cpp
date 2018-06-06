#include "gui/guimessage.h"
#include "gui/packetcolumnorder.h"

#include <QDebug>
#include <QTime>
#include <ctype.h>

void GuiMessage::fillEmpty()
{
    time = QTime::currentTime().toString("hh:mm:ss.zzz");
    source = "Source host";
    destination = "Destination host";
    type = "Type of message";
    code = "Mesage code";
    identifier = "Identifier of message";
    sequence = "Sequence number";
    data = "Message data";
}

QString GuiMessage::resolveICMPCode(uint8_t code, uint8_t type)
{
    switch (type) {
    case icmpMessageType::DestinationUnreachable:
        switch (code) {
        case icmpMessageCode::net_unreachable:
            return "net unreachable";
        case icmpMessageCode::port_unreachable:
                return "port unreachable";
        default:
                return QString::number(code);
        }
    default:
        return QString::number(type);
    }

}

QString GuiMessage::resolveICMPType(uint8_t type)
{
    switch (type) {
    case icmpMessageType::Echo:
        return "ECHO";
    case icmpMessageType::EchoReply:
        return "REPLY";
    case icmpMessageType::DestinationUnreachable:
        return "Destination unreachable";
    default:
        return QString::number(type);
    }
}

GuiMessage::GuiMessage()
{
   fillEmpty();
}

GuiMessage::GuiMessage(ICMPMessage &msgIn) : GuiMessage()
{
    type = resolveICMPType(msgIn.getType());
    code = resolveICMPCode(msgIn.getCode(), msgIn.getType());
    identifier = QString::number(msgIn.getIdentifier());
    sequence = QString::number(msgIn.getSequenceNumber());
    source = QString(msgIn.getSource().c_str());
    destination = QString(msgIn.getDestination().c_str());

    if(msgIn.getType() == icmpMessageType::Echo || msgIn.getType() == icmpMessageType::EchoReply){
        char * str = new char[msgIn.getDataLength()+1];
        memcpy(str, msgIn.getData(), msgIn.getDataLength());
        str[msgIn.getDataLength()] = 0;
        for(size_t i = 0; i < msgIn.getDataLength(); ++i)
        {
            if( !isprint(str[i]) ){
                str[i] = '.';
            }
        }
        data = QString(str);
    }
}

QString GuiMessage::getColumn(int index)
{
    switch (index)
    {
    case PacketColumnOrder::timestamp:
        return time;
    case PacketColumnOrder::source:
        return source;
    case PacketColumnOrder::destination:
        return destination;
    case PacketColumnOrder::type:
        return type;
    case PacketColumnOrder::code:
        return code;
    case PacketColumnOrder::identifier:
        return identifier;
    case PacketColumnOrder::sequence:
        return sequence;
    case PacketColumnOrder::data:
        return data;
    default:
        return QString("Not implemented");
    }
}
