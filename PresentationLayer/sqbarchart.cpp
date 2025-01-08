#include "sqbarchart.h"

SqBarChart::SqBarChart(QObject *parent)
    : QObject(parent), barSeries(new QBarSeries), yAxis(new QValueAxis), xAxis(new QBarCategoryAxis)
{
}

void SqBarChart::initializeChart(QChart *chart)
{
    // 清空之前的内容
    chart->removeAllSeries();
    chart->removeAxis(xAxis);
    chart->removeAxis(yAxis);

    // 添加柱状图系列到图表
    chart->addSeries(barSeries);

    // 配置 X 轴
    chart->addAxis(xAxis, Qt::AlignBottom);
    barSeries->attachAxis(xAxis);

    // 配置 Y 轴
    chart->addAxis(yAxis, Qt::AlignLeft);
    barSeries->attachAxis(yAxis);

    // 图表基本设置
    chart->setTitle("Bar Chart");
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
}

void SqBarChart::addData(const QStringList &categories, const QList<qreal> &values, const QString &label)
{
    // 清空现有数据
    barSeries->clear();
    xAxis->clear();

    // 添加分类
    xAxis->append(categories);

    // 添加数据
    QBarSet *barSet = new QBarSet(label);
    for (qreal value : values) {
        barSet->append(value);
    }
    barSeries->append(barSet);
}

void SqBarChart::clearData()
{
    barSeries->clear();
    xAxis->clear();
}

void SqBarChart::setAxisRange(qreal yMin, qreal yMax)
{
    yAxis->setRange(yMin, yMax);
}
