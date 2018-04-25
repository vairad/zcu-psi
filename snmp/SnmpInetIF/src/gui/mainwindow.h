#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeView>

#include "gui/treemodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    void refresh();
    bool toUpdate = true;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    TreeModel * model = NULL;
    QTreeView * view = NULL;


private:
    Ui::MainWindow *ui;

public slots:
    void handleConnection();
    void handleRefresh();
    void update();
};

#endif // MAINWINDOW_H
