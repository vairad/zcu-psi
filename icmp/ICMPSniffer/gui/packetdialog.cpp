#include "packetdialog.h"

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
    message->setDestination(hostname);

    if(resolveType() == icmpMessageType::Echo){
        std::string messageS = ui->lineEditEchoData->text().toUtf8().constData();
        message->setContent(messageS);
    }

    correctFlag = true;
    close();
}
