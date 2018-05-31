#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gui/packettablemodel.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    PacketTableModel *model;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void sendEcho();
};

#endif // MAINWINDOW_H
