#ifndef GUIMESSAGE_H
#define GUIMESSAGE_H

 #include <QString>

class GuiMessage
{

   QString destination;
   QString source;
   QString type;
   QString code;
   QString identifier;
   QString sequence;
   QString data;

public:
    GuiMessage();
    QString getColumn(int index);

};

#endif // GUIMESSAGE_H
