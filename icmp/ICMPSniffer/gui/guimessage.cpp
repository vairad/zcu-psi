#include "gui/guimessage.h"
#include "gui/packetcolumnorder.h"

#include <QDebug>

GuiMessage::GuiMessage()
{
    source = "TODO source";
    destination = "TODO destination";
    type = "TODO type";
    code = "TODO code";
    identifier = "TODO identifier";
    sequence = "TODO sequence";
    data = "TODO data";
    //todo set fields
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
