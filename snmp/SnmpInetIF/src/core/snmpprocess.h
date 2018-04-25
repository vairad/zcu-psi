#ifndef SNMPPROCESS_H
#define SNMPPROCESS_H

#include <mutex>

#include "core/snmpconnectiondetails.h"
#include "core/snmpdigger.h"
#include "core/snmpstate.h"

class SnmpProcess
{
    static void updateStructure(SnmpProcess *state);
    static InetInterface *lookupInterface(size_t index, SnmpProcess *process);

    static std::mutex mtx;
    static bool runningThread;



public:
    SNMPDigger *digger;
    SnmpState *state;
    SnmpProcess(SnmpConnectionDetails *connectionDetails);
    bool update();
    bool isRunning();
};

#endif // SNMPPROCESS_H
