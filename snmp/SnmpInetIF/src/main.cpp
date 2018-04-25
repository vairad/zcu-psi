#include <QApplication>
#include <QTreeView>

#include "gui/mainwindow.h"
#include "gui/treemodel.h"
#include "core/coreinterface.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();

//    QApplication app(argc, argv);

//    TreeModel model(NetInterface::getFoundedInterfaces());

//    QTreeView view;
//    view.setModel(&model);
//    view.setWindowTitle(QObject::tr("Simple Tree Model"));
//    view.show();
//    return app.exec();
}
