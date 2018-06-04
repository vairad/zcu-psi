#ifndef GUIINTERFACE_H
#define GUIINTERFACE_H

#include "gui/mainwindow.h"
#include "icmp/icmpmessage.h"



class GuiInterface
{
    static PacketTableModel *messages;
public:
    static void setGuiInterface(PacketTableModel * messages);
    static void addMessage(ICMPMessage message);
};

#endif // GUIINTERFACE_H
