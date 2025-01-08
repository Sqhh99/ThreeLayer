#ifndef LINECHARTPOINTCONVERSION_H
#define LINECHARTPOINTCONVERSION_H
#include "pointconversion.h"

class LineChartPointConversion : public PointConversion
{
public:
    explicit LineChartPointConversion(QObject *parent = nullptr);

    virtual QVector<QPointF> convertToPoints(const QStringList &data, bool &ok) override;
};

#endif // LINECHARTPOINTCONVERSION_H
