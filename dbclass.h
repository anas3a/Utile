#ifndef DBCLASS_H
#define DBCLASS_H
#include <QSqlDatabase>
#include <QDebug>

class dbclass
{
    public:
    QSqlDatabase db;
    dbclass();
    void connect();
    void disconnect();
};

#endif // DBCLASS_H
