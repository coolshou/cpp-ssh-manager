#ifndef COMMANDCONFIG_H
#define COMMANDCONFIG_H

#include "qlist.h"
#include "qstring.h"

class CommandConfig
{
public:
    CommandConfig();
    QList<QString> *ssh;
    QList<QString> *edit;
};

#endif // COMMANDCONFIG_H
