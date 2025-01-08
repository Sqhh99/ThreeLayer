#include "sqboxchart.h"

SqBoxChart::SqBoxChart(QObject *parent)
    : QObject(parent), boxSeries(new QBoxPlotSeries), yAxis(new QValueAxis), xAxis(new QBarCategoryAxis)
{
}

void SqBoxChart::initializeChart(QChart *chart)
{
    // 清空旧的内容
    chart->removeAllSeries();
    chart->removeAxis(xAxis);
    chart->removeAxis(yAxis);

    // 添加箱线图系列到图表
    chart->addSeries(boxSeries);

    // 配置 X 轴
    chart->addAxis(xAxis, Qt::AlignBottom);
    boxSeries->attachAxis(xAxis);

    // 配置 Y 轴
    chart->addAxis(yAxis, Qt::AlignLeft);
    boxSeries->attachAxis(yAxis);

    // 图表基本设置
    chart->setTitle("Box Plot");
    chart->legend()->setVisible(false);
}

void SqBoxChart::addData(const QStringList &categories, const QList<QList<qreal>> &dataSets)
{
    // 清空现有数据
    boxSeries->clear();
    xAxis->clear();

    // 检查数据完整性
    if (categories.size() != dataSets.size()) return;

    // 添加分类
    xAxis->append(categories);

    // 添加每组数据
    for (int i = 0; i < dataSets.size(); ++i) {
        const QList<qreal> &data = dataSets[i];
        if (data.size() == 5) { // 箱线图需要5个数据点
            QBoxSet *boxSet = new QBoxSet(categories[i]);
            boxSet->setValue(QBoxSet::LowerExtreme, data[0]);   // 最小值
            boxSet->setValue(QBoxSet::LowerQuartile, data[1]);  // 下四分位数
            boxSet->setValue(QBoxSet::Median, data[2]);         // 中位数
            boxSet->setValue(QBoxSet::UpperQuartile, data[3]);  // 上四分位数
            boxSet->setValue(QBoxSet::UpperExtreme, data[4]);   // 最大值
            boxSeries->append(boxSet);
        }
    }
}


void SqBoxChart::clearData()
{
    boxSeries->clear();
    xAxis->clear();
}

void SqBoxChart::setAxisRange(qreal yMin, qreal yMax)
{
    yAxis->setRange(yMin, yMax);
}
