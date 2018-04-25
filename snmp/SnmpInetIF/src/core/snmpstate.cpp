#include "snmpstate.h"

#include <mutex>

std::mutex SnmpState::mtx;

// Singleton implementation

SnmpState *SnmpState::INSTANCE = new SnmpState();

SnmpState::SnmpState()
{
    //do nothing
}

SnmpState *SnmpState::getInstance()
{
    return INSTANCE;
}
// End sigleton implementation //////////////////////////////////////////////////////////////////////////////////////////////////


void SnmpState::cleanCollection()
{
    std::lock_guard<std::mutex> lock(mtx);
    interfaces.clear();
}

void SnmpState::append(std::list<InetInterface *> list)
{
    std::lock_guard<std::mutex> lock(mtx);
    interfaces.insert(interfaces.end(), list.begin(), list.end());
}

std::list<InetInterface *> SnmpState::getInterfaceList()
{
    std::lock_guard<std::mutex> lock(mtx);
    std::list<InetInterface *> list = interfaces;
    return list;
}




