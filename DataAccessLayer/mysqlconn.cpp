#include "mysqlconn.h"
#include <QSqlTableModel>
#include <QTableView>

MysqlConn::MysqlConn() {}

bool MysqlConn::connMySql()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");  // 数据库主机地址
    db.setPort(3306);             // 数据库端口
    db.setDatabaseName("test"); // 数据库名称
    db.setUserName("root");       // 用户名
    db.setPassword("200400");   // 密码
    if (!db.open()) {
        qDebug() << "Failed to connect to database:" << db.lastError().text();
        return false;
    }

    return true;
}

QList<QStringList> MysqlConn::getTableData(const QString &tableName)
{
    // 存储数据的 QList<QStringList>
    QList<QStringList> dataList;

    // 创建 QSqlQuery 查询
    QSqlQuery query;
    if (!query.exec("SELECT * FROM " + tableName)) {
        qDebug() << "Query failed:" << query.lastError().text();
        return QList<QStringList>{};
    }

    // 添加表头
    QStringList headers;
    headers << "Date" << "Million Euros";
    dataList.append(headers);

    // 读取数据行
    while (query.next()) {
        QStringList row;
        row << query.value(0).toString()  // Date
            << query.value(1).toString(); // Million Euros
        dataList.append(row);
    }

    return dataList;
}
