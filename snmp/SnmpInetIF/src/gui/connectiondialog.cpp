#include "connectiondialog.h"

#include "ui_connectionform.h"
#include "core/snmpsecurity.h"

ConnectionDialog::ConnectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionDialog)
{
    ui->setupUi(this);

   // connect(ui->connectBT, SIGNAL(released()),this, SLOT(handleConnection()));
}

ConnectionDialog::~ConnectionDialog()
{
    delete ui;
}


SnmpSecurity ConnectionDialog::resolveSecurity(){
    QString comboS = ui->hashCombo->currentText();

    if( comboS == "MD5"){
        return SnmpSecurity::MD5;
    }
    if(comboS == "SHA1"){
        return SnmpSecurity::SHA1;
    }
    throw new std::exception();
}

SnmpConnectionDetails *ConnectionDialog::getConnectionDetails()
{
    std::string user = ui->usernameEdit->text().toUtf8().constData();
    std::string password = ui->passwordEdit->text().toUtf8().constData();
    std::string hostname = ui->hostEdit->text().toUtf8().constData();
    return new SnmpConnectionDetails(hostname, user, password, resolveSecurity());
}
