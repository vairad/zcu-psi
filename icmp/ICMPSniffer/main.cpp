#include "gui/mainwindow.h"
#include <QApplication>
#include <iostream>
#include "icmp/icmpmessage.h"
#include "icmp/icmputils.h"

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

int main(int argc, char *argv[])
{
   // return runGuiApp(argc, argv);
    return testCheckSum();
}
