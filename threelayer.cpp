#include "threelayer.h"
#include "./ui_threelayer.h"
#include "BusinessLogicLayer/linechartpointconversion.h"
#include "BusinessLogicLayer/pointmath.h"
#include "DataAccessLayer/mysqlconn.h"
#include "BusinessLogicLayer/linearregressionhelper.h"
#include "BusinessLogicLayer/mysqlconncontroller.h"

ThreeLayer::ThreeLayer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ThreeLayer)
    , csvController(new CsvController(this))
    , lineChart(new SqLineChart(this))
    , pieChart(new SqPieChart(this))
    , barChart(new SqBarChart(this))
    , boxChart(new SqBoxChart(this))
    , pointConversion(new LineChartPointConversion(this))
    , mysqlConnController(new MysqlConnController(this))
{
    ui->setupUi(this);
    connect(ui->action_csv, &QAction::triggered, this, &ThreeLayer::onAction_csv);
    connect(ui->BarChartAct, &QAction::triggered, this, &ThreeLayer::onBarChartAct);
    connect(ui->LineChartAct, &QAction::triggered, this, &ThreeLayer::onLineChartAct);
    connect(ui->ScatterPlotAct, &QAction::triggered, this, &ThreeLayer::onScatterPlotAct);
    connect(ui->dbConnAct, &QAction::triggered, this, &ThreeLayer::ondbConnAct);
    connect(mysqlConnController, &MysqlConnController::dataLoaded, this, &ThreeLayer::onSqlData);

    connect(csvController, &CsvController::dataLoaded, this, &ThreeLayer::updateTableView);
    connect(csvController, &CsvController::dataSaved, this, &ThreeLayer::onDataSaved);

    connect(pointConversion, &PointConversion::conversionError, this, &ThreeLayer::onConversionError);

    dbTableModel = new QStandardItemModel(this);
    ui->tableView->setModel(this->dbTableModel);
    mysqlConnController->loadSqlData("financial_data");

    this->DrawLineChart();

    this->DrawPieChart();

    this->DrawBarChart();

    this->DrawBoxChart();
}



ThreeLayer::~ThreeLayer()
{
    delete ui;
}

QList<QStringList> ThreeLayer::getSelectedColumnsData()
{
    QList<QStringList> selectedColumnsData;

    QItemSelectionModel *selectionModel = ui->tableView->selectionModel();
    if (!selectionModel->hasSelection()) {
        return selectedColumnsData;
    }

    QModelIndexList selectedIndexes = selectionModel->selectedColumns();

    for (const QModelIndex &columnIndex : selectedIndexes) {
        int col = columnIndex.column();
        QStringList columnData;

        for (int row = 0; row < ui->tableView->model()->rowCount(); ++row) {
            QModelIndex index = ui->tableView->model()->index(row, col);
            columnData.append(index.data().toString()); // 转为 QString
        }
        selectedColumnsData.append(columnData);
    }
    return selectedColumnsData;
}

void ThreeLayer::DrawLineChart() {
    if (data.size() <= 1) {
        qWarning() << "Data is empty or only contains headers.";
        return;}
    QChart *chart = ui->LineChart->chart();
    QStringList years;
    QVector<QPointF> line;
    for (int i = 1; i < data.size(); i++) {
        line.append(QPointF(i - 1, data[i][1].toDouble()));
        years.append(data[i][0]); }
    QVector<QVector<QPointF>> lines;
    lines.append(line);
    PointMath pm;
    qreal maxX, minX, maxY, minY;
    pm.calculateAxisRange(lines, maxX, minX, maxY, minY);
    lineChart->initializeChart(chart);
    lineChart->setXAxisType(true);
    chart->setTitle("折线图");
    LinearRegressionResult result = LinearRegressionHelper::performLinearRegression(data);
    QVector<QPointF> regressionLine;
    for (int i = 0 ; i < years.size(); ++i) {
        double y = result.slope * years[i].toDouble() + result.intercept;
        regressionLine.append(QPointF(i, y));}
    lineChart->addData(regressionLine, "Regression Line");
    lineChart->addData(line, "Original Data");
    lineChart->addCategoryLabels(years);
    lineChart->setAxisRange(0, years.size() - 1, minY, maxY);
    ui->LineChart->setRenderHint(QPainter::Antialiasing);
    ui->lineEdit_11->setText(QString::number(result.slope));
    ui->lineEdit_12->setText(QString::number(result.intercept));
    ui->lineEdit_13->setText(QString::number(result.correlationCoefficient));
    ui->lineEdit_14->setText("y = " + QString::number(result.slope) + "*x +" + QString::number(result.intercept));}


void ThreeLayer::DrawPieChart() {
    QChart *chart = ui->PieView->chart();
    QStringList categories;
    QList<qreal> values;
    for (int i = 1; i < data.size(); ++i) {
        categories.append(data[i][0]);
        values.append(data[i][1].toDouble()); }
    pieChart->initializeChart(chart);
    pieChart->addData(categories, values);
    ui->PieView->setRenderHint(QPainter::Antialiasing);
    std::vector<double> dataDouble;
    for (int i = 1; i < data.size(); i++) {dataDouble.push_back(data[i][1].toDouble());}
    StatsResult stats = PointMath::calculateMeanMedianMode(dataDouble);
    ui->lineEdit_8->setText(QString::number(stats.mean));
    ui->lineEdit_9->setText(QString::number(stats.median));
    ui->lineEdit_10->setText("每个值的频率都是1");}

void ThreeLayer::DrawBarChart(){
    QStringList categories;
    QList<qreal> values;
    for (int i = 1; i < data.size(); ++i) {
        categories.append(data[i][0]);
        values.append(data[i][1].toDouble());}
    QChart *chart = ui->BarView->chart();
    SqBarChart barChart;
    barChart.initializeChart(chart);
    barChart.addData(categories, values, "Million Euros");
    barChart.setAxisRange(0, *std::max_element(values.begin(), values.end()) * 1.1);
    ui->BarView->setRenderHint(QPainter::Antialiasing);}

void ThreeLayer::DrawBoxChart() {
    QList<QList<double>> boxChartData = PointMath::convertToBoxChartData(data);
    std::vector<double> dataDouble;
    for (int i = 1; i < data.size(); i++) {
        dataDouble.push_back(data[i][1].toDouble());}
    std::vector<double> percentilesToCalculate = {10, 50, 90};
    QStringList categories;
    categories.append("");
    QChart *chart = ui->BoxPlot->chart();
    SqBoxChart boxChart;
    boxChart.initializeChart(chart);
    boxChart.addData(categories, boxChartData);
    boxChart.setAxisRange(2000.0, 10000.0);
    ui->BoxPlot->setRenderHint(QPainter::Antialiasing);
    StatsResult stats = PointMath::calculateStats(dataDouble,percentilesToCalculate);
    ui->lineEdit->setText(QString::number(stats.stdDev));
    ui->lineEdit_2->setText(QString::number(stats.Q1));
    ui->lineEdit_3->setText(QString::number(stats.Q3));
    ui->lineEdit_4->setText(QString::number(stats.IQR));
    ui->lineEdit_5->setText(QString::number(stats.percentiles[0]));
    ui->lineEdit_6->setText(QString::number(stats.percentiles[1]));
    ui->lineEdit_7->setText(QString::number(stats.percentiles[2]));}

void ThreeLayer::onAction_csv()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(), tr("csv Files (*.csv);;All Files (*)"));

    if (!filePath.isEmpty())
    {
        csvController->clearData();
        dbTableModel->clear();
        csvController->loadCsv(filePath);
    }
}

void ThreeLayer::updateTableView()
{
    const QList<QStringList>& data = csvController->getData();
    // 设置表头
    QStringList headers = data[0];
    dbTableModel->setColumnCount(headers.size());
    dbTableModel->setHorizontalHeaderLabels(headers);

    // 填充数据
    for (int row = 1; row < data.size(); ++row) // 从第2行开始，跳过表头
    {
        QList<QStandardItem *> items;
        for (const QString &cell : data[row])
        {
            items.append(new QStandardItem(cell));
        }
        dbTableModel->appendRow(items);
    }

    // 优化表格显示
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // 自动拉伸列宽
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers); // 禁止编辑
    ui->tableView->setSelectionMode(QAbstractItemView::MultiSelection);  // 允许多选
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectColumns);  // 多列选择
}

void ThreeLayer::onDataSaved()
{
    QMessageBox::information(this, tr("Save Complete"), tr("CSV file saved successfully!"));
}

void ThreeLayer::onBarChartAct()
{
    QList<QStringList> selectedData = getSelectedColumnsData();

    for (const QStringList &column : selectedData) {
        qDebug() << "Selected Column:" << column;
    }
}

void ThreeLayer::onLineChartAct()
{
    QVector<QVector<QPointF>> lines;
    QChart *chart = ui->LineChart->chart();
    chart->removeAllSeries();
    bool ok;
    QList<QStringList> selectedData = getSelectedColumnsData();
    for (auto i : selectedData) {
        QVector<QPointF> point = pointConversion->convertToPoints(i, ok);
        if (ok) {
            lines.append(point);
        }
    }

    if (!lines.isEmpty()) {
        PointMath pm;
        qreal maxX, minX, maxY, minY;
        pm.calculateAxisRange(lines, maxX, minX, maxY, minY);
        lineChart->initializeChart(chart);

        chart->setTitle("折线图");
        for (auto line : lines) {
            lineChart->addData(line, "Line");
        }

        lineChart->setAxisRange(minX, maxX, minY, maxY);


    } else {
        QMessageBox::critical(nullptr, tr("错误"), tr("请选择数据"));
    }
}

void ThreeLayer::onScatterPlotAct()
{

}

void ThreeLayer::onConversionError(const QString &errorMessage)
{
    QMessageBox::critical(nullptr, tr("错误"), tr("请选择数值列"));
}

void ThreeLayer::ondbConnAct() {
    MysqlConn conn;
    if (conn.connMySql()) {
        dbTableModel->clear();
        data = conn.getTableData("financial_data");

        for (const QStringList &row : data) {
            qDebug() << row;
        }

        QStringList headers = data[0];
        dbTableModel->setColumnCount(headers.size());
        dbTableModel->setHorizontalHeaderLabels(headers);

        for (int row = 1; row < data.size(); ++row)
        {
            QList<QStandardItem *> items;
            for (const QString &cell : data[row])
            {
                items.append(new QStandardItem(cell));
            }
            dbTableModel->appendRow(items);
        }

        // 优化表格显示
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // 自动拉伸列宽
        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers); // 禁止编辑
        ui->tableView->setSelectionMode(QAbstractItemView::MultiSelection);  // 允许多选
        ui->tableView->setSelectionBehavior(QAbstractItemView::SelectColumns);  // 多列选择
    }
}

void ThreeLayer::onSqlData() {
    data = mysqlConnController->getData();
    for (const QStringList &row : data) {qDebug() << row;}
    QStringList headers = data[0];
    dbTableModel->setColumnCount(headers.size());
    dbTableModel->setHorizontalHeaderLabels(headers);
    for (int row = 1; row < data.size(); ++row){
        QList<QStandardItem *> items;
        for (const QString &cell : data[row]){items.append(new QStandardItem(cell));}
        dbTableModel->appendRow(items);}
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionMode(QAbstractItemView::MultiSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectColumns); }
