#include "csvcontroller.h"

#include <QDebug>

CsvController::CsvController(QObject *parent)
    : QObject(parent)
{
}

// 加载 CSV 文件
bool CsvController::loadCsv(const QString &filePath)
{
    QList<QStringList> data;
    if (SqCsv::readCsv(filePath, data)) {
        csvData = data; // 缓存数据到逻辑层
        emit dataLoaded(); // 通知 UI 层更新
        QMessageBox::information(nullptr, tr("成功"), tr("CSV文件加载成功！")); // 显示成功对话框
        return true;
    } else {
        QMessageBox::critical(nullptr, tr("错误"), tr("未能加载CSV文件。")); // 显示错误对话框
        return false;
    }
}

// 保存 CSV 文件
bool CsvController::saveCsv(const QString &filePath)
{
    if (SqCsv::writeCsv(filePath, csvData)) {
        emit dataSaved(); // 通知 UI 层保存成功
        QMessageBox::information(nullptr, tr("Success"), tr("CSV file saved successfully!")); // 显示成功对话框
        return true;
    } else {
        QMessageBox::critical(nullptr, tr("Error"), tr("Failed to save CSV file.")); // 显示错误对话框
        return false;
    }
}

// 获取当前数据
const QList<QStringList>& CsvController::getData() const
{
    return csvData;
}
void CsvController::clearData() { csvData.clear(); }
