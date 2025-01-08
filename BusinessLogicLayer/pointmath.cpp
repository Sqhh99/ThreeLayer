#include "PointMath.h"

PointMath::PointMath()
{
    // Constructor can be empty or used to initialize some values
}

void PointMath::calculateAxisRange(const QVector<QVector<QPointF>>& points,
                                   qreal& maxX, qreal& minX, qreal& maxY, qreal& minY)
{
    // Initialize with extreme values
    minX = std::numeric_limits<qreal>::max();
    maxX = std::numeric_limits<qreal>::lowest();
    minY = std::numeric_limits<qreal>::max();
    maxY = std::numeric_limits<qreal>::lowest();

    // Loop through the 2D QVector and calculate the ranges
    for (const auto& pointList : points) {
        for (const auto& point : pointList) {
            updateRange(point.x(), minX, maxX);
            updateRange(point.y(), minY, maxY);
        }
    }
}

QList<QList<double> > PointMath::convertToBoxChartData(const QList<QStringList> &data)
{
    QList<QList<double>> boxChartData;

    if (data.size() <= 1) return boxChartData; // 没有足够的数据

    // 提取数值部分
    QList<double> values;
    for (int i = 1; i < data.size(); ++i) { // 跳过表头
        bool ok = false;
        double value = data[i][1].toDouble(&ok); // 第二列是数值
        if (ok) values.append(value);
    }

    if (values.isEmpty()) return boxChartData;

    // 排序
    std::sort(values.begin(), values.end()); // 使用 std::sort 替代 qSort

    // 计算统计值
    double min = values.first();
    double max = values.last();
    double q1 = values[values.size() / 4];  // 下四分位数
    double median = values[values.size() / 2]; // 中位数
    double q3 = values[3 * values.size() / 4]; // 上四分位数

    // 存入箱线图数据
    boxChartData.append({min, q1, median, q3, max});

    return boxChartData;
}

void PointMath::updateRange(qreal value, qreal& minValue, qreal& maxValue)
{
    if (value < minValue) {
        minValue = value;
    }
    if (value > maxValue) {
        maxValue = value;
    }
}
double PointMath::calculatePercentile(const std::vector<double> &data,
                                      double percentile) {
    if (data.empty())
        return 0.0;

    double pos = percentile * (data.size() - 1) / 100.0;
    size_t index = static_cast<size_t>(pos);
    double fraction = pos - index;

    if (index + 1 < data.size())
        return data[index] + fraction * (data[index + 1] - data[index]);
    return data[index];
}
StatsResult PointMath::calculateStats(const std::vector<double> &data,
                          const std::vector<double> &percentilesToCalculate) {
    if (data.empty()) {
        throw std::invalid_argument("Data vector is empty");
    }

    // Sort data for percentile calculations
    std::vector<double> sortedData = data;
    std::sort(sortedData.begin(), sortedData.end());

    // Calculate mean
    double sum = 0.0;
    for (double value : data) {
        sum += value;
    }
    double mean = sum / data.size();

    // Calculate standard deviation
    double variance = 0.0;
    for (double value : data) {
        variance += (value - mean) * (value - mean);
    }
    variance /= data.size();
    double stdDev = std::sqrt(variance);

    // Calculate Q1, Q3, and IQR
    double Q1 = calculatePercentile(sortedData, 25);
    double Q3 = calculatePercentile(sortedData, 75);
    double IQR = Q3 - Q1;

    // Calculate specified percentiles
    std::vector<double> calculatedPercentiles;
    for (double p : percentilesToCalculate) {
        calculatedPercentiles.push_back(calculatePercentile(sortedData, p));
    }

    return {mean, stdDev, Q1, Q3, IQR, calculatedPercentiles};
}

StatsResult PointMath::calculateMeanMedianMode(const std::vector<double> &data) {
    if (data.empty()) {
        throw std::invalid_argument("Data vector is empty");
    }

    StatsResult result;
    std::vector<double> sortedData = data;
    std::sort(sortedData.begin(), sortedData.end());

    // Mean
    double sum = std::accumulate(sortedData.begin(), sortedData.end(), 0.0);
    result.mean = sum / sortedData.size();

    // Median
    size_t size = sortedData.size();
    if (size % 2 == 0) {
        result.median = (sortedData[size / 2 - 1] + sortedData[size / 2]) / 2.0;
    } else {
        result.median = sortedData[size / 2];
    }

    // Mode
    std::map<double, int> frequencyMap;
    for (double num : sortedData) {
        frequencyMap[num]++;
    }

    int maxFrequency = 0;
    for (const auto &entry : frequencyMap) {
        if (entry.second > maxFrequency) {
            maxFrequency = entry.second;
            result.modes.clear();
            result.modes.push_back(entry.first);
        } else if (entry.second == maxFrequency) {
            result.modes.push_back(entry.first);
        }
    }

    // 如果众数频率为1，则说明所有元素都只出现一次，不存在众数
    if (maxFrequency == 1) {
        result.modes.clear();
    }

    return result;
}
