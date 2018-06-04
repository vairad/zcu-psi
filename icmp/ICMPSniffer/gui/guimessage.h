#ifndef GUIMESSAGE_H
#define GUIMESSAGE_H

 #include <QString>

#include "icmp/icmpmessage.h"

class GuiMessage
{

   QString destination;
   QString source;
   QString type;
   QString code;
   QString identifier;
   QString sequence;
   QString data;

   void fillEmpty();

public:
    GuiMessage();
    GuiMessage(ICMPMessage &msgIn);
    QString getColumn(int index);

};

#endif // GUIMESSAGE_H
