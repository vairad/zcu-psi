#ifndef SNMPCONFIGURATION_H
#define SNMPCONFIGURATION_H

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>

class SnmpConfiguration
{    
public:
    static long version;
    static int securityLevel;
};

#endif // SNMPCONFIGURATION_H
