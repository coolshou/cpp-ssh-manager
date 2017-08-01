#ifndef CONFIG_H
#define CONFIG_H

#include <windowconfig.h>
#include <commandconfig.h>
#include <connection.h>
#include <qjsonarray.h>

class Config
{
public:
    Config();
    WindowConfig window;
    CommandConfig command;
    QList<Connection> connections;
    QList<QString> *getListFromJsonArray(QJsonArray array);
};

#endif // CONFIG_H
