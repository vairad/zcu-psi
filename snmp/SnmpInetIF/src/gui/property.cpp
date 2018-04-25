#include "property.h"

Property::Property(QString key, QString value, QString oid)
    : key(key), value(value), oid(oid)
{
}

QList<Property *> Property::PreparePropertyCollection(CoreInterface *interface)
{
    QList<Property *> properties;

    properties.append(new Property("Description", interface->getName()          , "IF-MIB::ifDescr"));
    properties.append(new Property("HW addr",       interface->getPhy()         , "IF-MIB::ifPhysAddress"));
    properties.append(new Property("Admin status",  interface->getAdminState()  , "IF-MIB::ifAdminStatus"));
    properties.append(new Property("MTU",           interface->getMTU()         , "IF-MIB::ifMtu"));
    properties.append(new Property("In bytes",      interface->getInBytes()     , "IF-MIB::ifInOctets"));
    properties.append(new Property("Out bytes",      interface->getOutBytes()   , "IF-MIB::ifOutOctets"));

    return properties;
}
