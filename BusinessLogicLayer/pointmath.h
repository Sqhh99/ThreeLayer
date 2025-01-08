#ifndef POINTMATH_H
#define POINTMATH_H

#include <QVector>
#include <QPointF>
#include <limits>
#include <algorithm>
#include <vector>
#include <cmath>
#include <map>

struct StatsResult {
    double mean;
    double stdDev;
    double Q1;
    double Q3;
    double IQR;
    std::vector<double> percentiles;
    double median;
    std::vector<double> modes;
};

class PointMath
{
public:
    PointMath();
    static double calculatePercentile(const std::vector<double> &data, double percentile);
    static StatsResult calculateStats(const std::vector<double> &data, const std::vector<double> &percentilesToCalculate);
    static StatsResult calculateMeanMedianMode(const std::vector<double> &data);

    void calculateAxisRange(const QVector<QVector<QPointF>>& points, qreal& maxX, qreal& minX, qreal& maxY, qreal& minY);
    static QList<QList<double>> convertToBoxChartData(const QList<QStringList> &data);

private:
    void updateRange(qreal value, qreal& minValue, qreal& maxValue);
};

#endif // POINTMATH_H
