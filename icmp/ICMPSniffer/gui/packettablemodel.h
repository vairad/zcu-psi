#ifndef PACKETTABLEMODEL_H
#define PACKETTABLEMODEL_H

#include "gui/guimessage.h"

#include <QAbstractTableModel>
#include <vector>

class PacketTableModel : public QAbstractTableModel
{
    const int COLUMN_COUNT = 7;
    std::vector<GuiMessage> messages;

public:
    PacketTableModel(QObject *parent);
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    void addNewMessage(GuiMessage message);

};

#endif // PACKETTABLEMODEL_H
