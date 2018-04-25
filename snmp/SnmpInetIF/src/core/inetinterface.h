#ifndef INETINTERFACE_H
#define INETINTERFACE_H

#include <string>

class InetInterface
{
    std::string adminState;
    std::string hwAdd;
    std::string MTU;
    std::string description;
    std::string inBytes;
    std::string outBytes;
    std::string name;

public:
    InetInterface();
    std::string getAdminState() const;
    std::string getHwAdd() const;
    std::string getMTU() const;
    std::string getDescription() const;
    void setAdminState(const int64_t &value);
    void setHwAdd(const std::string &value);
    void setMTU(const std::string &value);
    void setDescription(const std::string &value);
    std::string getInBytes() const;
    void setInBytes(const std::string &value);
    std::string getOutBytes() const;
    void setOutBytes(const std::string &value);
    std::string getName() const;
    void setName(const std::string &value);
};

#endif // INETINTERFACE_H
