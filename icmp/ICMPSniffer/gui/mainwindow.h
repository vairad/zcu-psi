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

    PacketTableModel &model;
public:
    explicit MainWindow(PacketTableModel &model, QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    const static double ColumnSourceSize;
    const static double ColumnDestinationSize;
    const static double ColumnTypeSize;
    const static double ColumnCodeSize;
    const static double ColumnIdentifierSize;
    const static double ColumnSequenceSize;
    const static double ColumnDataSize;


protected:
    virtual void resizeEvent(QResizeEvent *event);

private slots:
    void sendEcho();
};



#endif // MAINWINDOW_H
