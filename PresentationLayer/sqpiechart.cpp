#include "sqpiechart.h"

SqPieChart::SqPieChart(QObject *parent)
    : QObject(parent), pieSeries(new QPieSeries)
{
}

void SqPieChart::initializeChart(QChart *chart)
{
    // 添加饼图系列到图表
    chart->addSeries(pieSeries);

    // 图表基本设置
    // chart->setTitle("Pie Chart");

    // 设置图例竖直排列在左侧
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignLeft); // 图例对齐到左侧
    // chart->legend()->setOrientation(Qt::Vertical); // 设置图例为竖直方向
    chart->legend()->setMarkerShape(QLegend::MarkerShapeRectangle); // 图例标记为矩形（可选）
}

void SqPieChart::addData(const QStringList &categories, const QList<qreal> &values)
{
    pieSeries->clear();

    for (int i = 0; i < categories.size() && i < values.size(); ++i) {
        QPieSlice *slice = pieSeries->append(categories[i] + ": " + QString::number(values[i]), values[i]);

        slice->setLabelVisible(true); // 显示标签
        slice->setLabelPosition(QPieSlice::LabelOutside); // 将标签放置到饼块外部
        slice->setExploded(i == 0); // 突出显示第一个饼块
        slice->setPen(QPen(Qt::black, 1)); // 设置边框为黑色
        slice->setBrush(QColor::fromHsv(240 * i / categories.size(), 80, 255)); // 使用浅色系颜色
    }
}

void SqPieChart::clearData()
{
    pieSeries->clear();
}
