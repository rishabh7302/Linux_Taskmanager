
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

#include <QTimer>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTimer *systemStatsTimer;
    QPieSeries *cpuSeries;
    QPieSeries *ramSeries;
    QChart *cpuChart;
    QChart *ramChart;




    void showAllProcesses();
    void searchProcess();
    void setupCharts();
    void startSystemStatsUpdate();
    void updateSystemStats();
    void killSelectedProcess();
    void refreshWiFiInfo(); // For showing WiFi networks and connection status


};
#endif
