#include "gui/guimessage.h"
#include "gui/packetcolumnorder.h"

#include <QDebug>

void GuiMessage::fillEmpty()
{
    source = "TODO source";
    destination = "TODO destination";
    type = "TODO type";
    code = "TODO code";
    identifier = "TODO identifier";
    sequence = "TODO sequence";
    data = "TODO data";
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
}

QString GuiMessage::getColumn(int index)
{
    qDebug("reading message");
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
