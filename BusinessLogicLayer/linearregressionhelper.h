#ifndef LINEARREGRESSIONHELPER_H
#define LINEARREGRESSIONHELPER_H

#include <QVector>
#include <QPair>
#include <QList>
#include <QStringList>
#include <cmath>

struct LinearRegressionResult {
    double slope;
    double intercept;
    double correlationCoefficient;
};

class LinearRegressionHelper {
public:
    static LinearRegressionResult performLinearRegression(const QList<QList<QString>> &data);
};


#endif // LINEARREGRESSIONHELPER_H
