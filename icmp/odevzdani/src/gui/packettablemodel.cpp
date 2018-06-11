#include "gui/packettablemodel.h"
#include "gui/packetcolumnorder.h"

#include <QDebug>

PacketTableModel::PacketTableModel(QObject *parent)
    :QAbstractTableModel(parent)
{
}

int PacketTableModel::rowCount(const QModelIndex & /*parent*/) const
{
   return messages.size();
}

int PacketTableModel::columnCount(const QModelIndex & /*parent*/) const
{
    return COLUMN_COUNT;
}

QVariant PacketTableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
       GuiMessage message = messages.at(index.row());
       return message.getColumn(index.column());
    }
    return QVariant();
}


QVariant PacketTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
            case PacketColumnOrder::timestamp:
                return QString("Čas");
            case PacketColumnOrder::source:
                return QString("Zdroj");
            case PacketColumnOrder::destination:
                return QString("Cíl");
            case PacketColumnOrder::type:
                return QString("Typ");
            case PacketColumnOrder::code:
                return QString("Kód");
            case PacketColumnOrder::identifier:
                return QString("Identifikátor");
            case PacketColumnOrder::sequence:
                return QString("Pořadí");
            case PacketColumnOrder::data:
                return QString("Data");
            default:
                return QString("Not implemented");
            }
        }
        if (orientation == Qt::Vertical) {
            return QString::number(section+1);
        }
    }
    return QVariant();
}

void PacketTableModel::addNewMessage(GuiMessage message)
{
    int rowId = messages.size()-1;
    beginInsertRows(QModelIndex(), rowId,  rowId);
    messages.push_back(message);
    endInsertRows();
}
