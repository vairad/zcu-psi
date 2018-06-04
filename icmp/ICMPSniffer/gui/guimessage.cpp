#include "gui/guimessage.h"
#include "gui/packetcolumnorder.h"

#include <QDebug>

void GuiMessage::fillEmpty()
{
    source = "Source host";
    destination = "Destination host";
    type = "Type of message";
    code = "Mesage code";
    identifier = "Identifier of message";
    sequence = "Sequence number";
    data = "Message data";
}

GuiMessage::GuiMessage()
{
   fillEmpty();
}

GuiMessage::GuiMessage(ICMPMessage &msgIn) : GuiMessage()
{
    type = QString::number(msgIn.getType());
    code = QString::number(msgIn.getCode());
    identifier = QString::number(msgIn.getIdentifier());
    sequence = QString::number(msgIn.getSequenceNumber());

    if(msgIn.getType() == icmpMessageType::Echo){
        char * str = new char[msgIn.getDataLength()+1];
        memcpy(str, msgIn.getData(), msgIn.getDataLength());
        str[msgIn.getDataLength()] = 0;
        data = QString(str);
    }
}

QString GuiMessage::getColumn(int index)
{
    switch (index)
    {
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
