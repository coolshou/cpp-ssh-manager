#include "config.h"
#include <QVariant>
#include <QDebug>

Config::Config()
{

}

QList<QString> *Config::getListFromJsonArray(QJsonArray array)
{
    QList<QString> *stringList = new QList<QString>();
    for (QVariant item : array.toVariantList()){
        stringList->append(item.toString());
    }

    return stringList;
}
