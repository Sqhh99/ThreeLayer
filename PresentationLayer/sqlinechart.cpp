#include "sqlinechart.h"

SqLineChart::SqLineChart(QObject *parent)
    : QObject(parent),
    chart(nullptr),
    xAxisValue(new QValueAxis),
    xAxisCategory(new QCategoryAxis),
    yAxis(new QValueAxis),
    useCategoryAxis(false) // 默认使用 QValueAxis
{
}

void SqLineChart::initializeChart(QChart *chart)
{
    this->chart = chart;
    chart->setTitle("Line Chart");

    // 添加默认的 X 轴和 Y 轴
    chart->addAxis(xAxisValue, Qt::AlignBottom);
    chart->addAxis(yAxis, Qt::AlignLeft);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
}

void SqLineChart::addData(const QVector<QPointF> &points, const QString &seriesName)
{
    // 创建新的折线系列
    QLineSeries *series = new QLineSeries;
    series->append(points);
    series->setName(seriesName);

    // 添加系列到图表
    chart->addSeries(series);

    // 绑定坐标轴
    if (useCategoryAxis) {
        series->attachAxis(xAxisCategory);
    } else {
        series->attachAxis(xAxisValue);
    }
    series->attachAxis(yAxis);

    // 保存系列到列表
    lineSeriesList.append(series);
}

void SqLineChart::clearData()
{
    // 清空所有折线系列
    for (QLineSeries *series : lineSeriesList) {
        chart->removeSeries(series);
        delete series;
    }
    lineSeriesList.clear();
}

void SqLineChart::setAxisRange(qreal xMin, qreal xMax, qreal yMin, qreal yMax)
{
    if (!useCategoryAxis) {
        xAxisValue->setRange(xMin, xMax);
    }
    yAxis->setRange(yMin, yMax);
}

void SqLineChart::setXAxisType(bool useCategoryAxis)
{
    this->useCategoryAxis = useCategoryAxis;

    // 切换坐标轴类型
    if (useCategoryAxis) {
        chart->removeAxis(xAxisValue);
        chart->addAxis(xAxisCategory, Qt::AlignBottom);
    } else {
        chart->removeAxis(xAxisCategory);
        chart->addAxis(xAxisValue, Qt::AlignBottom);
    }
}

void SqLineChart::addCategoryLabels(const QStringList &labels)
{
    // 检查并移除现有的 X 轴
    if (chart->axes(Qt::Horizontal).contains(xAxisCategory)) {
        chart->removeAxis(xAxisCategory);
        delete xAxisCategory; // 删除旧的 X 轴
    }

    // 创建新的 X 轴
    xAxisCategory = new QCategoryAxis;

    // 添加类目标签
    qreal step = 1.0; // 假设每个类目间隔为 1
    qreal position = 0.0;
    for (const QString &label : labels) {
        xAxisCategory->append(label, position);
        position += step;
    }

    // 添加新轴并绑定到图表
    chart->addAxis(xAxisCategory, Qt::AlignBottom);

    // 重新绑定所有系列到新轴
    for (QLineSeries *series : lineSeriesList) {
        series->attachAxis(xAxisCategory);
        series->attachAxis(yAxis);
    }
}

