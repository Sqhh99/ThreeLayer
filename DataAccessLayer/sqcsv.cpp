#include "sqcsv.h"

SqCsv::SqCsv() {}

bool SqCsv::readCsv(QString filePath, QList<QStringList> &data)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream stream(&file);
    while (!stream.atEnd())
    {
        QString line = stream.readLine();
        QStringList row = line.split(',', Qt::SkipEmptyParts);
        data.append(row);
    }

    file.close();
    return true;
}

bool SqCsv::writeCsv(QString filePath,const QList<QStringList> &data)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream stream(&file);
    for (int i = 0; i < data.size(); i++)
    {
        QStringList row = data.at(i);
        for (int j = 0; j < row.size(); j++)
        {
            stream << row.at(j);
            if (j < row.size() - 1)
                stream << ",";
        }
        stream << "\n";
    }

    file.close();
    return true;
}
