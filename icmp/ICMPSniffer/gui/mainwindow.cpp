#include "gui/mainwindow.h"
#include "ui_mainwindow.h"

#include "gui/packetcolumnorder.h"

#include <QTableView>
#include <QDebug>


const double MainWindow::ColumnSourceSize = 0.2;
const double MainWindow::ColumnDestinationSize = ColumnSourceSize;
const double MainWindow::ColumnTypeSize = 0.05;
const double MainWindow::ColumnCodeSize = ColumnTypeSize;
const double MainWindow::ColumnIdentifierSize = 0.1;
const double MainWindow::ColumnSequenceSize = 0.1;
const double MainWindow::ColumnDataSize = 0.3;


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

     connect(ui->actionSendEcho, &QAction::triggered, this, &MainWindow::sendEcho);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendEcho()
{
    qDebug("SendEchoAction");
    model.addNewMessage(*new GuiMessage());
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
