#ifndef CONNECTIONLISTMODEL_H
#define CONNECTIONLISTMODEL_H

#include <QAbstractItemModel>
#include <connection.h>

class ConnectionListModel : public QAbstractItemModel
{
    Q_OBJECT
public:



    void setConnections(QList<Connection> connections);
signals:

public slots:

private:
    QList<Connection> connections;
};

#endif // CONNECTIONLISTMODEL_H
