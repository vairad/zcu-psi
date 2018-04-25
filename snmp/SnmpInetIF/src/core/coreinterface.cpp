#include <QDebug>

#include "coreinterface.h"

#include "core/snmpprocess.h"

QList<CoreInterface *> CoreInterface::FoundedInterfacesList;

SnmpProcess * CoreInterface::process = NULL;


QString CoreInterface::getName() const
{
    return name;
}

QString CoreInterface::getPhy() const
{
    return phy;
}

QString CoreInterface::getAdminState() const
{
    return adminState;
}

QString CoreInterface::getMTU() const
{
    return MTU;
}

QString CoreInterface::getInBytes() const
{
    return inBytes;
}

QString CoreInterface::getOutBytes() const
{
    return outBytes;
}

QString CoreInterface::getAdminName() const
{
    return adminName;
}

CoreInterface::CoreInterface(QString name, QString phy, QString adminState, QString MTU, QString inBytes, QString outBytes, QString adminName)
    : name(name), phy(phy), adminState(adminState), MTU(MTU), inBytes(inBytes), outBytes(outBytes)
    , adminName(adminName)
{

}

const QList<CoreInterface *> &CoreInterface::getFoundedInterfaces()
{
    return CoreInterface::FoundedInterfacesList;
}

bool CoreInterface::isUpdating()
{
    return process->isRunning();
}

void CoreInterface::reconnect(SnmpConnectionDetails *details)
{
    if (process){
        delete process;
    }
    process = new SnmpProcess(details);
    loadData();
}

void CoreInterface::loadData()
{
    if(!process->update()){
        throw new std::exception();
    }
   loadState();
}

void CoreInterface::loadState()
{
    if(process && process->state)
    {
        auto list = process->state->getInterfaceList();
        FoundedInterfacesList.clear();
        for(InetInterface * iface : list)
        {
            FoundedInterfacesList.push_back(
                new CoreInterface(QString::fromStdString(iface->getDescription())
                                  ,QString::fromStdString(iface->getHwAdd())
                                  , QString::fromStdString(iface->getAdminState())
                                  , QString::fromStdString(iface->getMTU())
                                   , QString::fromStdString(iface->getInBytes())
                                   , QString::fromStdString(iface->getOutBytes())
                                  , QString::fromStdString(iface->getName()))
                        );
        }
    }

}
