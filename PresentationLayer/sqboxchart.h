#ifndef SQBOXCHART_H
#define SQBOXCHART_H

#include <QObject>
#include <QChart>
#include <QBoxPlotSeries>
#include <QBoxSet>
#include <QValueAxis>
#include <QBarCategoryAxis>

class SqBoxChart : public QObject
{
    Q_OBJECT

public:
    explicit SqBoxChart(QObject *parent = nullptr);

    void initializeChart(QChart *chart);                 // 初始化箱线图
    void addData(const QStringList &categories,          // 添加数据
                 const QList<QList<qreal>> &dataSets);
    void clearData();                                    // 清空数据
    void setAxisRange(qreal yMin, qreal yMax);           // 设置Y轴范围

private:
    QBoxPlotSeries *boxSeries;   // 箱线图系列
    QValueAxis *yAxis;           // Y轴
    QBarCategoryAxis *xAxis;     // X轴
};

#endif // SQBOXCHART_H
