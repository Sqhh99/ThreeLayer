#ifndef MYSQLCONNCONTROLLER_H
#define MYSQLCONNCONTROLLER_H

#include "../DataAccessLayer/mysqlconn.h"

class MysqlConnController : public QObject
{
    Q_OBJECT

public:
    explicit MysqlConnController(QObject *parent = nullptr);

    bool loadSqlData(const QString &tableName);

    QList<QStringList> getData();

private:
    QList<QStringList> sqlData;

signals:
    void dataLoaded();
};

#endif // MYSQLCONNCONTROLLER_H
