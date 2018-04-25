#include <QTreeView>
#include <QMessageBox>
#include <QTimer>

#include "ui_mainwindow.h"

#include "gui/connectiondialog.h"
#include "gui/mainwindow.h"
#include "gui/treemodel.h"

#include "core/coreinterface.h"


void MainWindow::refresh()
{
    try
    {
        TreeModel *oldModel = model;
        CoreInterface::loadState();
        model = new TreeModel(CoreInterface::getFoundedInterfaces());
        ui->treeView->setModel(model);
        QModelIndexList indexes = model->match(model->index(0,0), Qt::DisplayRole, "*", -1, Qt::MatchWildcard|Qt::MatchRecursive);
        foreach (QModelIndex index, indexes){
            ui->treeView->expand(index);
        }
        if(oldModel != NULL){
            delete oldModel;
        }
    }catch(...)
    {
        //load state failed there is no data
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    model(new TreeModel(CoreInterface::getFoundedInterfaces())),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->treeView->setModel(model);

    ui->progressBar->setVisible(false);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(5000);

//    QTimer *timerRefresh = new QTimer(this);
//    connect(timerRefresh, SIGNAL(timeout()), this, SLOT(handleRefresh()));
//    timer->start(10000);

    connect(ui->connectBT, SIGNAL(released()),this, SLOT(handleConnection()));
    connect(ui->reloadBT, SIGNAL(released()),this, SLOT(handleRefresh()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleConnection()
{
    ConnectionDialog dialog(this);
    dialog.setVisible(true);
    const auto returned = dialog.exec();
    if(returned == QDialog::Accepted)
    {
        ui->progressBar->setVisible(true);
        SnmpConnectionDetails *details = dialog.getConnectionDetails();
        if(details->isOk())
        {
            try{
              CoreInterface::reconnect(details);
            }catch(...){
                QMessageBox msgBox;
                msgBox.setText("Connection failed");
                msgBox.setStandardButtons( QMessageBox::Ok);
                msgBox.exec();
            }
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setText("Incomplete connection parameters");
            msgBox.setStandardButtons( QMessageBox::Ok);
            msgBox.exec();
        }
    }
}

void MainWindow::handleRefresh()
{
    try{
        ui->progressBar->setVisible(true);
        CoreInterface::loadData();
    }catch(...){
        QMessageBox msgBox;
        msgBox.setText("Connection failed");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }
}

void MainWindow::update()
{
    if(CoreInterface::isUpdating())
    {
         ui->progressBar->setVisible(true);
         toUpdate = true;
    }else{
        ui->progressBar->setVisible(false);
        refresh();
    }

//    if(CoreInterface::fail){
//        CoreInterface::fail = false;
//        QMessageBox msgBox;
//        msgBox.setText(QString::fromStdString(CoreInterface::fail_msg));
//        msgBox.setStandardButtons(QMessageBox::Ok);
//        msgBox.exec();
//    }

}

