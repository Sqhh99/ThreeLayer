#include "mysqlconncontroller.h"

MysqlConnController::MysqlConnController(QObject *parent)
    : QObject(parent)
{
}

bool MysqlConnController::loadSqlData(const QString &tableName)
{
    MysqlConn sqlConn;
    if (sqlConn.connMySql()) {
        sqlData = sqlConn.getTableData(tableName);
        emit dataLoaded();
        return true;
    }
    return false;
}

QList<QStringList> MysqlConnController::getData()
{
    return sqlData;
}
