#ifndef SQBARCHART_H
#define SQBARCHART_H

#include <QObject>
#include <QChart>
#include <QBarSeries>
#include <QBarSet>
#include <QValueAxis>
#include <QChartView>
#include <QBarCategoryAxis>

// QT_CHARTS_USE_NAMESPACE

class SqBarChart : public QObject
{
    Q_OBJECT

public:
    explicit SqBarChart(QObject *parent = nullptr);

    void initializeChart(QChart *chart);                // 初始化柱状图
    void addData(const QStringList &categories,         // 添加数据
                 const QList<qreal> &values,
                 const QString &label);
    void clearData();                                   // 清空数据
    void setAxisRange(qreal yMin, qreal yMax);          // 设置Y轴范围

private:
    QBarSeries *barSeries;    // 柱状图系列
    QValueAxis *yAxis;        // Y轴
    QBarCategoryAxis *xAxis;  // X轴
};

#endif // SQBARCHART_H
