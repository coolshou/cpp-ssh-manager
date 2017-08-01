#ifndef CONNECTION_H
#define CONNECTION_H

#include <qstring.h>
#include <qlist.h>
#include <qmetatype.h>
#include <qvariant.h>

class Connection
{
public:
    Connection();
    QString host;
    QString label;
    int port;
    QList<QString> args;

    QString toString() {
        return label;
    }
};
Q_DECLARE_METATYPE(Connection)

#endif // CONNECTION_H
