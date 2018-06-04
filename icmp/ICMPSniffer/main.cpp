#include <QApplication>
#include <iostream>

#include <icmp/messenger.h>

#include "gui/guiinterface.h"
#include "gui/mainwindow.h"
#include "gui/packettablemodel.h"
#include "icmp/icmpmessage.h"
#include "icmp/icmputils.h"
#include "icmp/sender.h"

int testCheckSum(){
    ICMPMessage message;
    message.setType(icmpMessageType::Echo);
    message.setContent("TEST");
    message.setIdentifier(1);
    message.setSequenceNumber(9);
    uint16_t result = ICMPUtils::computeCheckSum(message);
    std::cout << std::hex << result;
}

int testSendEcho(){
    Sender sender("localhost");

    ICMPMessage *message = new ICMPMessage();
    message->setType(icmpMessageType::Echo);
    message->setContent("TEST");
    message->setIdentifier(1);
    message->setSequenceNumber(9);

    Messenger::getToSend().push_msg(message);
}

int runGuiApp(int argc, char* argv[]){
    QApplication a(argc, argv);

    Sender sender("localhost");

    PacketTableModel model(0);
    GuiInterface::setGuiInterface(&model);
    MainWindow w(model);

    w.show();
    return a.exec();
}


int main(int argc, char *argv[])
{
   return runGuiApp(argc, argv);
}
