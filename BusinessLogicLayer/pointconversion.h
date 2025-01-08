#ifndef POINTCONVERSION_H
#define POINTCONVERSION_H

#include <QObject>
#include <QPointF>

class PointConversion : public QObject
{
    Q_OBJECT
public:
    explicit PointConversion(QObject *parent = nullptr);

    virtual QVector<QPointF> convertToPoints(const QStringList &data, bool &ok) = 0;

    virtual ~PointConversion() = default;

signals:
    // 转换错误信号
    virtual void conversionError(const QString &errorMessage);
};

#endif // POINTCONVERSION_H
