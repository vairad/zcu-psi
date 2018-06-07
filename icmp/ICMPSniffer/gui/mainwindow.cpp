#include "gui/mainwindow.h"
#include "packetdialog.h"
#include "ui_mainwindow.h"

#include "gui/packetcolumnorder.h"

#include <QTableView>
#include <QDebug>
#include <QInputDialog>
#include <QMessageBox>

#include <icmp/exceptions.h>
#include <icmp/messagefactory.h>
#include <icmp/messenger.h>


const double MainWindow::ColumnSourceSize = 0.15;
const double MainWindow::ColumnDestinationSize = ColumnSourceSize;
const double MainWindow::ColumnTypeSize = 0.10;
const double MainWindow::ColumnCodeSize = ColumnTypeSize;
const double MainWindow::ColumnIdentifierSize = 0.09;
const double MainWindow::ColumnSequenceSize = 0.09;
const double MainWindow::ColumnDataSize = 0.5;


MainWindow::MainWindow(PacketTableModel &model,QWidget *parent) :
    QMainWindow(parent),
    model(model),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTableView *view = ui->packets;
        view->setModel(&this->model);
        view->show();

        view->setEditTriggers(QAbstractItemView::NoEditTriggers);

     connect(ui->actionSendEchoLocalhost, &QAction::triggered, this, &MainWindow::sendEchoLocalhost);
     connect(ui->actionSendEcho, &QAction::triggered, this, &MainWindow::sendEcho);
     connect(ui->actionGenerateICMP, &QAction::triggered, this, &MainWindow::sendGenerateICMP);

     connect(ui->sendEchoButton, SIGNAL(clicked()), this, SLOT(sendEcho()));
     connect(ui->sendLocalhostButton, SIGNAL(clicked()), this, SLOT(sendEchoLocalhost()));
     connect(ui->generateButton, SIGNAL(clicked()), this, SLOT(sendGenerateICMP()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

std::string MainWindow::readUserString(QString valueName)
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                             valueName, QLineEdit::Normal,
                                             "", &ok);
    if (ok && !text.isEmpty()){
            std::string utf8_text = text.toUtf8().constData();
            return utf8_text;
    }
    return "";
}

void MainWindow::sendEcho()
{
    qDebug("SendEcho triggered");
    std::string hostname = readUserString(tr("Hostname: "));
    try{
            Messenger::getToSend().push_msg(MessageFactory::createEchoTest(hostname));
    }
    catch(DNSException &e){
        QMessageBox msgBox;
        std::string message = "Hostname: ";
        message += e.what();
        message += " se nepodařilo přeložit.";
        msgBox.setText(message.c_str());
        msgBox.exec();
    }

}

void MainWindow::sendEchoLocalhost()
{
    qDebug("SendEchoLocalhost triggered");
    Messenger::getToSend().push_msg(MessageFactory::createEchoTest());
}

void MainWindow::sendGenerateICMP()
{
    qDebug("SendGenerateICMP triggered");
    PacketWindow packetDlg(0);
    packetDlg.exec();

    if(packetDlg.correct()){
         Messenger::getToSend().push_msg(packetDlg.getMessage());
    }else{
        QMessageBox msgBox;
        std::string message = "Nebylo možné vytvořit ICMP packet";
        msgBox.setText(message.c_str());
        msgBox.exec();
    }
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    ui->packets->setColumnWidth(PacketColumnOrder::source, this->width() * ColumnSourceSize);
    ui->packets->setColumnWidth(PacketColumnOrder::destination, this->width() * ColumnDestinationSize);
    ui->packets->setColumnWidth(PacketColumnOrder::type, this->width() * ColumnTypeSize);
    ui->packets->setColumnWidth(PacketColumnOrder::code, this->width() * ColumnCodeSize);
    ui->packets->setColumnWidth(PacketColumnOrder::identifier, this->width() * ColumnIdentifierSize);
    ui->packets->setColumnWidth(PacketColumnOrder::sequence, this->width() * ColumnSequenceSize);
    ui->packets->setColumnWidth(PacketColumnOrder::data, this->width() * ColumnDataSize);

    QMainWindow::resizeEvent(event);
}
