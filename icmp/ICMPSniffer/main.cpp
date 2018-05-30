#include <QApplication>
#include <iostream>

#include "gui/mainwindow.h"
#include "icmp/icmpmessage.h"
#include "icmp/icmputils.h"
#include "icmp/sender.h"

int runGuiApp(int argc, char* argv[]){
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

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
    Sender sender("127.0.0.1");

    ICMPMessage message;
    message.setType(icmpMessageType::Echo);
    message.setContent("TEST");
    message.setIdentifier(1);
    message.setSequenceNumber(9);

    sender.sendMessage(message);
}

int main(int argc, char *argv[])
{
   testCheckSum();
   testSendEcho();
  // return runGuiApp(argc, argv);
}
