#ifndef MYSQLCONN_H
#define MYSQLCONN_H

#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>

class MysqlConn
{
public:
    MysqlConn();

    bool connMySql();

    QList<QStringList> getTableData(const QString &tableName);

private:
    QSqlDatabase db;
};

#endif // MYSQLCONN_H
