#include "linechartpointconversion.h"

LineChartPointConversion::LineChartPointConversion(QObject *parent) : PointConversion(parent){}

QVector<QPointF> LineChartPointConversion::convertToPoints(const QStringList &data, bool &ok)
{
    QVector<QPointF> points;
    ok = true;

    for (int i = 0; i < data.size(); ++i) {
        const QString &value = data[i];

        bool yOk;
        double y = value.toDouble(&yOk);

        if (!yOk) {
            emit conversionError(QString("Non-numeric value at row %1: %2").arg(i).arg(value));
            ok = false;
            points.clear();
            return points;
        }

        points.append(QPointF(i, y));
    }

    return points;
}
