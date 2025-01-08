#ifndef SQLINECHART_H
#define SQLINECHART_H

#include <QObject>
#include <QChart>
#include <QLineSeries>
#include <QValueAxis>
#include <QCategoryAxis>
#include <QChartView>

class SqLineChart : public QObject
{
    Q_OBJECT

public:
    explicit SqLineChart(QObject *parent = nullptr);

    // 初始化图表
    void initializeChart(QChart *chart);

    // 添加单条折线数据
    void addData(const QVector<QPointF> &points, const QString &seriesName);

    // 清空所有折线数据
    void clearData();

    // 设置坐标轴范围
    void setAxisRange(qreal xMin, qreal xMax, qreal yMin, qreal yMax);

    // 设置横轴类型 (QValueAxis 或 QCategoryAxis)
    void setXAxisType(bool useCategoryAxis);

    // 添加分类轴标签
    void addCategoryLabels(const QStringList &labels);

private:
    QChart *chart;                         // 图表对象
    QList<QLineSeries *> lineSeriesList;   // 管理多个折线系列
    QValueAxis *xAxisValue;                // 数值型 X 轴
    QCategoryAxis *xAxisCategory;          // 分类型 X 轴
    QValueAxis *yAxis;                     // Y 轴
    bool useCategoryAxis;                  // 是否使用分类轴
};

#endif // SQLINECHART_H
