#include "dbclass.h"
dbclass::dbclass()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("D:/utile/utiledb.db");
}

 void dbclass::connect()
{
     //connection to database

    if (db.open())
        qDebug() << "db connected" << Qt::endl;
    else
        qDebug() << "can't connect db" << Qt::endl;
}

void dbclass::disconnect()
{
    //disconnecting database

    db.close();
    qDebug() << "db disconnected" << Qt::endl;
}
