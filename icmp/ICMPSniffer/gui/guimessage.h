#ifndef GUIMESSAGE_H
#define GUIMESSAGE_H

 #include <QString>

#include "icmp/icmpmessage.h"
#include "icmp/icmpdefinitions.h"

class GuiMessage
{
   QString time;
   QString destination;
   QString source;
   QString type;
   QString code;
   QString identifier;
   QString sequence;
   QString data;

   void fillEmpty();

   static QString resolveICMPCode(uint8_t code, uint8_t type);
   static QString resolveICMPType(uint8_t type);


public:
    GuiMessage();
    GuiMessage(ICMPMessage &msgIn);
    QString getColumn(int index);

};

#endif // GUIMESSAGE_H
