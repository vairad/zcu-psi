#include "guiinterface.h"

PacketTableModel * GuiInterface::messages;


void GuiInterface::setGuiInterface(PacketTableModel *messages)
{
    GuiInterface::messages = messages;
}

void GuiInterface::addMessage(ICMPMessage message)
{
    GuiMessage guiMes(message);
    messages->addNewMessage(guiMes);
}
