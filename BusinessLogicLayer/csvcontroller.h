#ifndef CSVCONTROLLER_H
#define CSVCONTROLLER_H

#include <QObject>
#include <QList>
#include <QStringList>
#include "../DataAccessLayer/sqcsv.h"
#include <QMessageBox> // 引入 QMessageBox

class CsvController : public QObject
{
    Q_OBJECT

public:
    explicit CsvController(QObject *parent = nullptr);

    bool loadCsv(const QString &filePath);

    bool saveCsv(const QString &filePath);

    void clearData();

    const QList<QStringList>& getData() const;

signals:
    void dataLoaded();

    void dataSaved();

private:
    QList<QStringList> csvData;
};

#endif // CSVCONTROLLER_H
