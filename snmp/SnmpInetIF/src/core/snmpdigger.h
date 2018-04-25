#ifndef SNMPDIGGER_H
#define SNMPDIGGER_H

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <string>

#include "core/snmpsecurity.h"
#include "core/snmpconnectiondetails.h"

class SNMPDigger
{
    netsnmp_session session, *ss;

    void setUpAuth(std::string name, std::string password, SnmpSecurity security);

    void setSecurityProtocol(SnmpSecurity security);

    const SnmpConnectionDetails *connectionDetails;

public:
    SNMPDigger(SnmpConnectionDetails *details);
    ~SNMPDigger();

    bool askSNMPQuestion(std::string asked_oid);

    bool askSNMPforInteger64(std::string asked_oid, int64_t &number);
    bool askSNMPforString(std::string asked_oid, std::string &string, bool hex);
};

#endif // SNMPDIGGER_H
