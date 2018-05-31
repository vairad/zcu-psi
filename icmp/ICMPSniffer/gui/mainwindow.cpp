#include "gui/mainwindow.h"
#include "ui_mainwindow.h"

#include <QTableView>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new PacketTableModel(0);

    QTableView *view = ui->packets;
        view->setModel(model);
        view->show();

        view->setEditTriggers(QAbstractItemView::NoEditTriggers);

 //       model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
  //      model->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
   //     model->setHeaderData(2, Qt::Horizontal, QObject::tr("City"));
    //    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Country"));

     connect(ui->actionSendEcho, &QAction::triggered, this, &MainWindow::sendEcho);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendEcho()
{
    qDebug("SendEchoAction");
    model->addNewMessage(*new GuiMessage());
}
