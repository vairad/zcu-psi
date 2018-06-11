#include "gui/packetdialog.h"
#include "icmp/exceptions.h"

#include <iostream>
#include <QMessageBox>

uint8_t PacketWindow::resolveCode()
{
    QString comboS = ui->comboBoxCode->currentText();

    if( comboS == "Echo"){
        return icmpMessageType::Echo;
    }
    if(comboS == "Echo reply"){
        return icmpMessageType::EchoReply;
    }
    return 0;
}

uint8_t PacketWindow::resolveType()
{
    QString comboS = ui->comboBoxType->currentText();

    if( comboS == "Echo"){
        return icmpMessageType::Echo;
    }
    if(comboS == "Echo reply"){
        return icmpMessageType::EchoReply;
    }
    if(comboS == "Timestamp"){
        return icmpMessageType::Timestamp;
    }
    if(comboS == "Destination uneachable"){
        return icmpMessageType::DestinationUnreachable;
    }
    if(comboS == "Information request"){
        return icmpMessageType::Information_Request;
    }
    return 0;
}

uint16_t PacketWindow::resolveIdentifier()
{
    return ui->spinBoxIdentifier->value();
}

uint16_t PacketWindow::resolveSequenceNumber()
{
    return ui->spinBoxSequence->value();
}

PacketWindow::PacketWindow(QWidget *parent):
       QDialog(parent),
       ui(new Ui::PacketDialog)
{
   ui->setupUi(this);
   connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(close()));
   connect(ui->createButton, SIGNAL(clicked()), this, SLOT(createICMP()));
   connect(ui->comboBoxType, SIGNAL(activated(int)),this,SLOT(typeValidation(int)));
   correctFlag = false;
}

PacketWindow::~PacketWindow()
{
    delete ui;
}

bool PacketWindow::correct()
{
    return correctFlag;
}

ICMPMessage *PacketWindow::getMessage()
{
    return message;
}

void PacketWindow::createICMP()
{
    message = new ICMPMessage();
    message->setCode(resolveCode());
    message->setType(resolveType());
    message->setIdentifier(resolveIdentifier());
    message->setSequenceNumber(resolveSequenceNumber());
    std::string hostname = ui->lineEditHostname->text().toUtf8().constData();

    try{
          message->setDestination(hostname);
    }catch( DNSException &e){
        std::string errMsg = "Could not resolve hostname: ";
        errMsg += e.what();
        std::cout << errMsg;

        QMessageBox msgBox;
        msgBox.setText(errMsg.c_str());
        msgBox.exec();

        correctFlag = false;
        return;
    }


    if(resolveType() == icmpMessageType::Echo){
        std::string messageS = ui->lineEditEchoData->text().toUtf8().constData();
        message->setContent(messageS);
    }
    if(resolveType() == icmpMessageType::Timestamp){
        message->prepareTimeData();
        message->setTime1();
    }

    correctFlag = true;
    close();
}

void PacketWindow::typeValidation(int choosed)
{
    if(choosed == 0){
        ui->lineEditEchoData->clear();
        ui->lineEditEchoData->setDisabled(false);
    }else{
        ui->lineEditEchoData->clear();
        ui->lineEditEchoData->setDisabled(true);
    }
}
