#ifndef SNMPSTATE_H
#define SNMPSTATE_H

#include <list>
#include <mutex>

#include "inetinterface.h"
/**
 * Singleton class that contains information about all found interfaces.
 * @brief The SnmpState class
 */
class SnmpState
{
    SnmpState();
    static SnmpState * INSTANCE;

    std::list<InetInterface *> interfaces;

    static std::mutex mtx;

public:
    static SnmpState *getInstance();

    void cleanCollection();
    void append(std::list<InetInterface *> list);
    std::list<InetInterface *> getInterfaceList();
};

#endif // SNMPSTATE_H
