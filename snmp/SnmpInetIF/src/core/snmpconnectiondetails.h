#ifndef SNMPCONNECTIONDETAILS_H
#define SNMPCONNECTIONDETAILS_H

#include <string>

#include "snmpsecurity.h"

class SnmpConnectionDetails
{
    std::string hostname;
    std::string username;
    std::string password;
    SnmpSecurity security;

public:

    SnmpConnectionDetails( std::string hostname, std::string username
                     , std::string password, SnmpSecurity security);

    std::string getHostname() const;
    std::string getUsername() const;
    std::string getPassword() const;
    SnmpSecurity getSecurity() const;
    bool isOk();
};

#endif // SNMPCONNECTIONDETAILS_H
