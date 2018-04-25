#include "snmpconnectiondetails.h"


std::string SnmpConnectionDetails::getUsername() const
{
    return username;
}

std::string SnmpConnectionDetails::getPassword() const
{
    return password;
}

SnmpSecurity SnmpConnectionDetails::getSecurity() const
{
    return security;
}

bool SnmpConnectionDetails::isOk()
{
    return hostname.length() > 0 && username.length() > 0 && password.length() > 0;
}

SnmpConnectionDetails::SnmpConnectionDetails(std::string hostname, std::string username, std::string password, SnmpSecurity security):
    hostname(hostname),
    username(username),
    password(password),
    security(security)
{

}

std::string SnmpConnectionDetails::getHostname() const
{
    return hostname;
}
