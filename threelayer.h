#ifndef THREELAYER_H
#define THREELAYER_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QTableView>
#include <QFileDialog>
#include <QFile>
#include <QDir>
#include "BusinessLogicLayer/csvcontroller.h"
#include "PresentationLayer/sqlinechart.h"
#include "BusinessLogicLayer/pointconversion.h"
#include "PresentationLayer/sqpiechart.h"
#include "BusinessLogicLayer/mysqlconncontroller.h"
#include "PresentationLayer/sqbarchart.h"
#include "PresentationLayer/sqboxchart.h"
#include <QChartView>
#include <QChart>

QT_BEGIN_NAMESPACE
namespace Ui {
class ThreeLayer;
}
QT_END_NAMESPACE

class ThreeLayer : public QMainWindow
{
    Q_OBJECT

public:
    ThreeLayer(QWidget *parent = nullptr);
    ~ThreeLayer();

private:
    QList<QStringList> data;
    QStandardItemModel* dbTableModel;
    CsvController* csvController;
    SqLineChart* lineChart;
    SqPieChart* pieChart;
    SqBarChart* barChart;
    SqBoxChart* boxChart;
    MysqlConnController* mysqlConnController;
    PointConversion* pointConversion;
    Ui::ThreeLayer *ui;
    QList<QStringList> getSelectedColumnsData();
    QStringList getSelectedColumnsName();

private:
    // void clearChartView();

private slots:
    void DrawLineChart();
    void DrawPieChart();
    void DrawBarChart();
    void DrawBoxChart();
    void onAction_csv();
    void updateTableView();
    void onDataSaved();
    void onBarChartAct();
    void onLineChartAct();
    void onScatterPlotAct();
    void ondbConnAct();
    void onSqlData();
    void onConversionError(const QString &errorMessage);
};
#endif // THREELAYER_H
