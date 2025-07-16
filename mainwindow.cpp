#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QTableWidgetItem>
#include <pwd.h>      // for username
#include <unistd.h>
#include <QProcess>
#include <QMessageBox>

#include <QTimer>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QLineSeries>

#include <QVBoxLayout>
#include <QRegularExpression>
#include <QLabel>
#include <QFont>
#include <QBrush>
#include <QPen>
#include <QMovie>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Set a sleek dark background for the main window
    this->setStyleSheet(
        "QMainWindow {"
        "  background-color: #121212;"
        "}"
        );

    // Style buttons
    QString buttonStyle = R"(
        QPushButton {
            background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                              stop:0 #4CAF50, stop:1 #2E7D32);
            border: none;
            border-radius: 12px;
            color: white;
            font-weight: 600;
            font-size: 14px;
            padding: 10px 20px;
            min-width: 100px;
            box-shadow: 2px 2px 5px rgba(0,0,0,0.6);
            transition: background-color 0.3s ease;
        }
        QPushButton:hover {
            background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                              stop:0 #66BB6A, stop:1 #388E3C);
        }
        QPushButton:pressed {
            background-color: #1B5E20;
        }
    )";


    // Apply styles
    ui->btnShowAll->setStyleSheet(buttonStyle);
    ui->btnSearch->setStyleSheet(buttonStyle);
    ui->btnProcessPage->setStyleSheet(buttonStyle);
    ui->btnStatsPage->setStyleSheet(buttonStyle);
    ui->btnKillProcess->setStyleSheet(buttonStyle);
    ui->btnWiFiPage->setStyleSheet(buttonStyle);
    ui->btnRefreshWiFi->setStyleSheet(buttonStyle);

    // Set cursors
    ui->btnShowAll->setCursor(Qt::PointingHandCursor);
    ui->btnSearch->setCursor(Qt::PointingHandCursor);
    ui->btnProcessPage->setCursor(Qt::PointingHandCursor);
    ui->btnStatsPage->setCursor(Qt::PointingHandCursor);
    ui->btnKillProcess->setCursor(Qt::PointingHandCursor);
    ui->btnWiFiPage->setCursor(Qt::PointingHandCursor);
    ui->btnRefreshWiFi->setCursor(Qt::PointingHandCursor);

    // Signal-slot connections
    connect(ui->btnShowAll, &QPushButton::clicked, this, &MainWindow::showAllProcesses);
    connect(ui->btnSearch, &QPushButton::clicked, this, &MainWindow::searchProcess);

    connect(ui->btnProcessPage, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentIndex(0);
    });

    connect(ui->btnStatsPage, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentIndex(1);
    });

    connect(ui->btnWiFiPage, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentIndex(2);  // Adjust index if needed
        refreshWiFiInfo();
    });

    connect(ui->btnKillProcess, &QPushButton::clicked, this, &MainWindow::killSelectedProcess);

    // WiFi page logic


    connect(ui->btnRefreshWiFi, &QPushButton::clicked, this, &MainWindow::refreshWiFiInfo);

    // Initialize charts and system updates
    setupCharts();
    startSystemStatsUpdate();
}


void MainWindow::showAllProcesses() {
    ui->tableProcesses->setRowCount(0);

    QProcess process;
    process.start("ps", QStringList() << "-eo" << "pid,comm,state,rss,user");
    process.waitForFinished();

    QString output = process.readAllStandardOutput();
    QStringList lines = output.split('\n', Qt::SkipEmptyParts);

    for (int i = 1; i < lines.size(); ++i) {
        QString line = lines[i].simplified();
        QStringList fields = line.split(' ', Qt::SkipEmptyParts);
        if (fields.size() < 5) continue;

        int row = ui->tableProcesses->rowCount();
        ui->tableProcesses->insertRow(row);
        ui->tableProcesses->setItem(row, 0, new QTableWidgetItem(fields[0]));  // PID
        ui->tableProcesses->setItem(row, 1, new QTableWidgetItem(fields[1]));  // Command
        ui->tableProcesses->setItem(row, 2, new QTableWidgetItem(fields[2]));  // State
        ui->tableProcesses->setItem(row, 3, new QTableWidgetItem(fields[3] + " KB"));  // Memory
        ui->tableProcesses->setItem(row, 4, new QTableWidgetItem(fields[4]));  // User
    }
}

void MainWindow::killSelectedProcess() {
    QList<QTableWidgetItem *> selectedItems = ui->tableProcesses->selectedItems();
    if (selectedItems.isEmpty()) {
        QMessageBox::warning(this, "No Selection", "Please select a process to kill.");
        return;
    }

    int row = selectedItems.first()->row();
    QString pid = ui->tableProcesses->item(row, 0)->text();

    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Kill Process",
        "Are you sure you want to kill process PID: " + pid + "?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes) {
        int exitCode = QProcess::execute("kill", QStringList() << "-9" << pid);
        if (exitCode == 0) {
            QMessageBox::information(this, "Success", "Process " + pid + " killed.");
        } else {
            QMessageBox::warning(this, "Error", "Failed to kill process " + pid + ".");
        }
        showAllProcesses(); // Refresh process list
    }
}


void MainWindow::searchProcess() {
    QString query = ui->lineSearch->text().trimmed();
    if (query.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a process name or PID to search.");
        return;
    }

    ui->tableProcesses->setRowCount(0); // Clear table

    QProcess process;
    process.start("ps", QStringList() << "-eo" << "pid,comm,state,rss,user");
    process.waitForFinished();

    QString output = process.readAllStandardOutput();
    QStringList lines = output.split('\n', Qt::SkipEmptyParts);

    bool found = false;

    // Skip the header
    for (int i = 1; i < lines.size(); ++i) {
        QString line = lines[i].simplified();
        QStringList fields = line.split(' ', Qt::SkipEmptyParts);

        if (fields.size() < 5) continue;

        QString pid = fields[0];
        QString name = fields[1];

        if (pid == query || name.contains(query, Qt::CaseInsensitive)) {
            int row = ui->tableProcesses->rowCount();
            ui->tableProcesses->insertRow(row);

            ui->tableProcesses->setItem(row, 0, new QTableWidgetItem(pid));
            ui->tableProcesses->setItem(row, 1, new QTableWidgetItem(name));
            ui->tableProcesses->setItem(row, 2, new QTableWidgetItem(fields[2])); // State
            ui->tableProcesses->setItem(row, 3, new QTableWidgetItem(fields[3] + " KB")); // Memory
            ui->tableProcesses->setItem(row, 4, new QTableWidgetItem(fields[4])); // User

            found = true;
        }
    }

    if (!found) {
        QMessageBox::information(this, "No Result", "No matching process found.");
    }
}




void MainWindow::setupCharts() {
    // --- CPU Pie Chart ---
    cpuSeries = new QPieSeries();
    cpuSeries->append("Used", 65);
    cpuSeries->append("Idle", 35);
    cpuSeries->setLabelsVisible(true);
    cpuSeries->setHoleSize(0.35);
    cpuSeries->setPieStartAngle(30);
    cpuSeries->setPieEndAngle(390);

    // Apply gradient for 3D effect on slices
    for (auto slice : cpuSeries->slices()) {
        QLinearGradient gradient(slice->labelPosition(), 0, 0, slice->labelPosition());
        gradient.setColorAt(0, slice->brush().color().lighter(150));
        gradient.setColorAt(1, slice->brush().color().darker(150));
        slice->setBrush(gradient);
        slice->setExploded(true);
        slice->setLabelVisible(true);
    }

    cpuChart = new QChart();
    cpuChart->addSeries(cpuSeries);
    cpuChart->setTitle("CPU Usage");
    cpuChart->setAnimationOptions(QChart::SeriesAnimations);

    QChartView *cpuView = new QChartView(cpuChart);
    cpuView->setRenderHint(QPainter::Antialiasing);
    cpuView->setMinimumHeight(250);

    // CPU usage over time (line chart)
    QLineSeries *cpuLineSeries = new QLineSeries();
    cpuLineSeries->append(0, 40);
    cpuLineSeries->append(1, 50);
    cpuLineSeries->append(2, 55);
    cpuLineSeries->append(3, 65);
    cpuLineSeries->append(4, 60);
    cpuLineSeries->append(5, 70);
    cpuLineSeries->append(6, 65);

    QChart *cpuLineChart = new QChart();
    cpuLineChart->addSeries(cpuLineSeries);
    cpuLineChart->createDefaultAxes();
    cpuLineChart->setTitle("CPU Usage Over Time");
    cpuLineChart->legend()->hide();
    cpuLineChart->setAnimationOptions(QChart::SeriesAnimations);

    QChartView *cpuLineView = new QChartView(cpuLineChart);
    cpuLineView->setRenderHint(QPainter::Antialiasing);
    cpuLineView->setMinimumHeight(150);

    // --- RAM Pie Chart ---
    ramSeries = new QPieSeries();
    ramSeries->append("Used", 6200);
    ramSeries->append("Free", 9800);
    ramSeries->setLabelsVisible(true);
    ramSeries->setHoleSize(0.35);
    ramSeries->setPieStartAngle(45);
    ramSeries->setPieEndAngle(405);

    for (auto slice : ramSeries->slices()) {
        QLinearGradient gradient(slice->labelPosition(), 0, 0, slice->labelPosition());
        gradient.setColorAt(0, slice->brush().color().lighter(150));
        gradient.setColorAt(1, slice->brush().color().darker(150));
        slice->setBrush(gradient);
        slice->setExploded(true);
        slice->setLabelVisible(true);
    }

    ramChart = new QChart();
    ramChart->addSeries(ramSeries);
    ramChart->setTitle("RAM Usage");
    ramChart->setAnimationOptions(QChart::SeriesAnimations);

    QChartView *ramView = new QChartView(ramChart);
    ramView->setRenderHint(QPainter::Antialiasing);
    ramView->setMinimumHeight(250);

    // RAM usage over time (line chart)
    QLineSeries *ramLineSeries = new QLineSeries();
    ramLineSeries->append(0, 5000);
    ramLineSeries->append(1, 5500);
    ramLineSeries->append(2, 6000);
    ramLineSeries->append(3, 6200);
    ramLineSeries->append(4, 6100);
    ramLineSeries->append(5, 6000);
    ramLineSeries->append(6, 5900);

    QChart *ramLineChart = new QChart();
    ramLineChart->addSeries(ramLineSeries);
    ramLineChart->createDefaultAxes();
    ramLineChart->setTitle("RAM Usage Over Time");
    ramLineChart->legend()->hide();
    ramLineChart->setAnimationOptions(QChart::SeriesAnimations);

    QChartView *ramLineView = new QChartView(ramLineChart);
    ramLineView->setRenderHint(QPainter::Antialiasing);
    ramLineView->setMinimumHeight(150);

    // Add CPU charts to layout
    QVBoxLayout *cpuLayout = new QVBoxLayout(ui->cpuChartContainer);
    cpuLayout->addWidget(cpuView);
    cpuLayout->addWidget(cpuLineView);

    // Add RAM charts to layout
    QVBoxLayout *ramLayout = new QVBoxLayout(ui->ramChartContainer);
    ramLayout->addWidget(ramView);
    ramLayout->addWidget(ramLineView);
}

void MainWindow::startSystemStatsUpdate() {
    systemStatsTimer = new QTimer(this);
    connect(systemStatsTimer, &QTimer::timeout, this, &MainWindow::updateSystemStats);
    systemStatsTimer->start(2000); // Update every 2 seconds
}

void MainWindow::updateSystemStats() {
    // --- Fetch CPU Usage using full path to mpstat ---
    QProcess cpuProcess;
    cpuProcess.start("/usr/bin/mpstat", {"1", "1"});
    cpuProcess.waitForFinished();
    QString cpuOutput = cpuProcess.readAllStandardOutput();
    qDebug() << "[mpstat output]\n" << cpuOutput;

    QStringList cpuLines = cpuOutput.split("\n", Qt::SkipEmptyParts);

    long cpuUsage = 0;
    for (const QString &line : cpuLines) {
        if (line.contains("all")) {
            QStringList cpuValues = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
            if (cpuValues.size() >= 12) {
                // %idle is usually the last column
                bool ok;
                double idle = cpuValues.last().toDouble(&ok);
                if (ok) {
                    cpuUsage = static_cast<long>(100 - idle);
                }
            }
            break;
        }
    }

    qDebug() << "CPU Usage -> Active: " << cpuUsage << "%";

    // --- Fetch RAM Usage using free -m ---
    QProcess ramProcess;
    ramProcess.start("/usr/bin/free", {"-m"});
    ramProcess.waitForFinished();
    QString ramOutput = ramProcess.readAllStandardOutput();
    qDebug() << "[free output]\n" << ramOutput;

    QStringList ramLines = ramOutput.split("\n", Qt::SkipEmptyParts);

    long totalRAM = 0, usedRAM = 0, freeRAM = 0;
    for (const QString &line : ramLines) {
        if (line.startsWith("Mem:")) {
            QStringList ramValues = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
            if (ramValues.size() >= 7) {
                totalRAM = ramValues[1].toLong();
                usedRAM = ramValues[2].toLong();
                freeRAM = ramValues[3].toLong() + ramValues[5].toLong(); // free + buff/cache
            }
            break;
        }
    }

    qDebug() << "RAM Usage -> Total:" << totalRAM << "MB, Free:" << freeRAM << "MB, Used:" << usedRAM << "MB";

    // --- Update Pie Charts ---
    cpuSeries->clear();
    QPieSlice *activeCpuSlice = cpuSeries->append("Active CPU", cpuUsage);
    QPieSlice *idleCpuSlice = cpuSeries->append("Idle CPU", 100 - cpuUsage);

    ramSeries->clear();
    QPieSlice *usedRamSlice = ramSeries->append("Used RAM", usedRAM);
    QPieSlice *freeRamSlice = ramSeries->append("Free RAM", freeRAM);

    // Add labels with names and values
    activeCpuSlice->setLabel(QString("Active CPU: %1%").arg(cpuUsage));
    idleCpuSlice->setLabel(QString("Idle CPU: %1%").arg(100 - cpuUsage));

    usedRamSlice->setLabel(QString("Used RAM: %1 MB of %2 MB").arg(usedRAM).arg(totalRAM));
    freeRamSlice->setLabel(QString("Free RAM: %1 MB of %2 MB").arg(freeRAM).arg(totalRAM));

    // Ensure labels are visible
    activeCpuSlice->setLabelVisible(true);
    idleCpuSlice->setLabelVisible(true);
    usedRamSlice->setLabelVisible(true);
    freeRamSlice->setLabelVisible(true);

    // Set label colors to white
    activeCpuSlice->setLabelBrush(QBrush(Qt::white));
    idleCpuSlice->setLabelBrush(QBrush(Qt::white));
    usedRamSlice->setLabelBrush(QBrush(Qt::white));
    freeRamSlice->setLabelBrush(QBrush(Qt::white));

    cpuChart->update();
    ramChart->update();
}


void MainWindow::refreshWiFiInfo() {
    qDebug() << "[WiFi] Refreshing WiFi Info...";

    // Show connected SSID
    QProcess getConnected;
    getConnected.start("nmcli", QStringList() << "-t" << "-f" << "active,ssid" << "dev" << "wifi");
    getConnected.waitForFinished();
    QString connectedOutput = getConnected.readAllStandardOutput();
    qDebug() << "[WiFi] Connected output:\n" << connectedOutput;

    QString currentSSID = "None";
    QStringList lines = connectedOutput.split('\n', Qt::SkipEmptyParts);
    for (const QString &line : lines) {
        QStringList parts = line.split(":");
        if (parts.size() > 1 && parts[0] == "yes") {
            currentSSID = parts[1];
            break;
        }
    }
    ui->labelConnectedWiFi->setText("Connected WiFi: " + currentSSID);

    // Get available networks
    QProcess listWiFi;
    listWiFi.start("nmcli", QStringList() << "device" << "wifi" << "list");
    listWiFi.waitForFinished();
    QString output = listWiFi.readAllStandardOutput();
    qDebug() << "[WiFi] Available networks output:\n" << output;

    ui->listWiFiNetworks->clear();

    // Skip header and split by line
    QStringList wifiLines = output.split('\n', Qt::SkipEmptyParts);
    for (int i = 1; i < wifiLines.size(); ++i) {
        QString line = wifiLines[i].simplified();
        QStringList parts = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
        if (parts.size() >= 8) {
            QString ssid = parts[0];
            QString signal = parts[6]; // Usually SIGNAL is at index 6
            ui->listWiFiNetworks->addItem(ssid + " (" + signal + "% signal)");
        }
    }
}


MainWindow::~MainWindow() {
    delete ui;
}
