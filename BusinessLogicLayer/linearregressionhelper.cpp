#include "linearregressionhelper.h"

LinearRegressionResult LinearRegressionHelper::performLinearRegression(
    const QList<QList<QString>> &data) {
    QVector<double> x, y;

    // Extract numeric values from data
    for (const auto &row : data) {
        x.append(row[0].toDouble()); // Year
        y.append(row[1].toDouble()); // Value
    }

    int n = x.size();
    if (n < 2)
        throw std::invalid_argument("Not enough data points for regression.");

    // Calculate means
    double sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0, sumY2 = 0;
    for (int i = 0; i < n; ++i) {
        sumX += x[i];
        sumY += y[i];
        sumXY += x[i] * y[i];
        sumX2 += x[i] * x[i];
        sumY2 += y[i] * y[i];
    }
    double meanX = sumX / n;
    double meanY = sumY / n;

    // Calculate slope (m) and intercept (b)
    double numerator = sumXY - n * meanX * meanY;
    double denominator = sumX2 - n * meanX * meanX;
    double slope = numerator / denominator;
    double intercept = meanY - slope * meanX;

    // Calculate correlation coefficient (r)
    double correlationNumerator = (sumXY - n * meanX * meanY);
    double correlationDenominator =
        std::sqrt((sumX2 - n * meanX * meanX) * (sumY2 - n * meanY * meanY));
    double correlationCoefficient = correlationNumerator / correlationDenominator;

    return {slope, intercept, correlationCoefficient};
}
