#ifndef PACKETDIALOG_H
#define PACKETDIALOG_H

#include <QDialog>

#include <icmp/icmpmessage.h>

#include "ui_packetdialog.h"

namespace Ui {
class PacketDialog;
}

class PacketWindow : public QDialog
{
   Q_OBJECT
public:
    PacketWindow(QWidget *parent = 0);
    ~PacketWindow();
    bool correct();
    ICMPMessage * getMessage();

private slots:
    void createICMP();

private:

    ICMPMessage *message;
    bool correctFlag;

    Ui::PacketDialog *ui;

    uint8_t resolveCode();
    uint8_t resolveType();
    uint16_t resolveIdentifier();
    uint16_t resolveSequenceNumber();
};

#endif // PACKETDIALOG_H
