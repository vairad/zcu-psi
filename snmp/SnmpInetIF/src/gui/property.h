#ifndef PROPERTY_H
#define PROPERTY_H

#include <QString>
#include <QList>

#include "core/coreinterface.h"

class Property
{
public:
    Property(QString key, QString value, QString oid);
    const QString key;
    const QString value;
    const QString oid;

    static QList<Property *> PreparePropertyCollection(CoreInterface *interface);

};

#endif // PROPERTY_H
