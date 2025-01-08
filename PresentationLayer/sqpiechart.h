#ifndef SQPIECHART_H
#define SQPIECHART_H

#include <QObject>
#include <QChart>
#include <QPieSeries>
#include <QChartView>

// QT_CHARTS_USE_NAMESPACE

class SqPieChart : public QObject
{
    Q_OBJECT

public:
    explicit SqPieChart(QObject *parent = nullptr);

    void initializeChart(QChart *chart);                // 初始化饼图
    void addData(const QStringList &categories,         // 添加数据
                 const QList<qreal> &values);
    void clearData();                                   // 清空数据

private:
    QPieSeries *pieSeries;   // 饼图系列
};

#endif // SQPIECHART_H
