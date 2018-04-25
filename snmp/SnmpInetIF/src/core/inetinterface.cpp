#include "inetinterface.h"

std::string InetInterface::getAdminState() const
{
    return adminState;
}

std::string InetInterface::getHwAdd() const
{
    return hwAdd;
}

std::string InetInterface::getMTU() const
{
    return MTU;
}

std::string InetInterface::getDescription() const
{
    return description;
}

void InetInterface::setAdminState(const int64_t &value)
{
    switch (value) {
    case 1:
        adminState = "Up";
        return;
    case 2:
        adminState = "Down";
        return;
    case 3:
        adminState = "Testing";
        return;
    default:
        adminState = "Unknown";
        return;
    }
}

void InetInterface::setHwAdd(const std::string &value)
{
    hwAdd = value;
}

void InetInterface::setMTU(const std::string &value)
{
    MTU = value;
}

void InetInterface::setDescription(const std::string &value)
{
    description = value;
}

std::string InetInterface::getInBytes() const
{
    return inBytes;
}

void InetInterface::setInBytes(const std::string &value)
{
    inBytes = value;
}

std::string InetInterface::getOutBytes() const
{
    return outBytes;
}

void InetInterface::setOutBytes(const std::string &value)
{
    outBytes = value;
}

std::string InetInterface::getName() const
{
    return name;
}

void InetInterface::setName(const std::string &value)
{
    name = value;
}

InetInterface::InetInterface()
{

}
