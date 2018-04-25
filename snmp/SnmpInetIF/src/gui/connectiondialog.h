#ifndef CONNECTIONDIALOG_H
#define CONNECTIONDIALOG_H

#include <QDialog>

#include "core/snmpconnectiondetails.h"

namespace Ui {
class ConnectionDialog;
}

class ConnectionDialog : public QDialog
{
    Q_OBJECT
public:
    ConnectionDialog(QWidget *parent = 0);
    ~ConnectionDialog();

    SnmpConnectionDetails *getConnectionDetails();

private:
    Ui::ConnectionDialog *ui;
    SnmpSecurity resolveSecurity();
};

#endif // CONNECTIONDIALOG_H
