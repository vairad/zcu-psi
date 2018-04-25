#ifndef INTERFACE_H
#define INTERFACE_H

#include <QString>
#include <QList>

#include "core/snmpconnectiondetails.h"
#include "core/snmpprocess.h"

/**
 * Class which is interface between QtGui and c++ core
 * @brief The NetInterface class
 */
class CoreInterface
{
     static QList<CoreInterface *> FoundedInterfacesList;
     static SnmpProcess * process;

     QString name;
     QString phy;
     QString adminState;
     QString MTU;
     QString inBytes;
     QString outBytes;
     QString adminName;

public:
    CoreInterface(QString name, QString phy, QString adminState
                  , QString MTU, QString inBytes, QString outBytes
                  , QString adminName);

    static const QList<CoreInterface *> &getFoundedInterfaces();
    static bool isUpdating();
    static void reconnect(SnmpConnectionDetails *details);
    static void loadData();
    static void loadState();
    QString getName() const;
    QString getPhy() const;
    QString getAdminState() const;
    QString getMTU() const;
    QString getInBytes() const;
    QString getOutBytes() const;
    QString getAdminName() const;

//  static bool fail;
//    static std::string fail_msg;

};

#endif // INTERFACE_H
