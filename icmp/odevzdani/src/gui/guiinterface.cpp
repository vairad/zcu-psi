#include "gui/guiinterface.h"

PacketTableModel * GuiInterface::messages;

std::mutex GuiInterface::message_lock;

void GuiInterface::setGuiInterface(PacketTableModel *messages)
{
    GuiInterface::messages = messages;
}

void GuiInterface::addMessage(ICMPMessage message)
{
    std::lock_guard<std::mutex> lock(message_lock);
    GuiMessage guiMes(message);
    messages->addNewMessage(guiMes);
}
