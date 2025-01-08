#ifndef SQCSV_H
#define SQCSV_H
#include <QStringList>
#include <QTextStream>
#include <QFile>

class SqCsv
{
public:
    SqCsv();

    // 读取CSV文件
    static bool readCsv(QString filePath, QList<QStringList>& data);

    // 写入CSV文件
    static bool writeCsv(QString filePath,const QList<QStringList>& data);


};

#endif // SQCSV_H
