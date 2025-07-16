/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QPushButton *btnProcessPage;
    QPushButton *btnStatsPage;
    QPushButton *btnWiFiPage;
    QStackedWidget *stackedWidget;
    QWidget *pageProcess;
    QTableWidget *tableProcesses;
    QPushButton *btnShowAll;
    QPushButton *btnSearch;
    QLineEdit *lineSearch;
    QPushButton *btnKillProcess;
    QWidget *pageStats;
    QWidget *ramChartContainer;
    QWidget *cpuChartContainer;
    QWidget *page;
    QListWidget *listWiFiNetworks;
    QLabel *labelConnectedWiFi;
    QPushButton *btnRefreshWiFi;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1104, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(10, 70, 201, 311));
        btnProcessPage = new QPushButton(widget);
        btnProcessPage->setObjectName("btnProcessPage");
        btnProcessPage->setGeometry(QRect(20, 20, 161, 41));
        QFont font;
        font.setFamilies({QString::fromUtf8("Ubuntu Sans Mono")});
        font.setBold(true);
        btnProcessPage->setFont(font);
        btnStatsPage = new QPushButton(widget);
        btnStatsPage->setObjectName("btnStatsPage");
        btnStatsPage->setGeometry(QRect(20, 90, 161, 41));
        btnStatsPage->setFont(font);
        btnWiFiPage = new QPushButton(widget);
        btnWiFiPage->setObjectName("btnWiFiPage");
        btnWiFiPage->setGeometry(QRect(20, 150, 121, 41));
        QFont font1;
        font1.setBold(true);
        btnWiFiPage->setFont(font1);
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(200, 20, 851, 481));
        pageProcess = new QWidget();
        pageProcess->setObjectName("pageProcess");
        tableProcesses = new QTableWidget(pageProcess);
        if (tableProcesses->columnCount() < 5)
            tableProcesses->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableProcesses->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableProcesses->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableProcesses->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableProcesses->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableProcesses->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableProcesses->setObjectName("tableProcesses");
        tableProcesses->setGeometry(QRect(20, 80, 811, 371));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("C059")});
        font2.setBold(true);
        tableProcesses->setFont(font2);
        tableProcesses->setAlternatingRowColors(true);
        tableProcesses->setShowGrid(true);
        tableProcesses->setGridStyle(Qt::PenStyle::SolidLine);
        tableProcesses->setColumnCount(5);
        tableProcesses->horizontalHeader()->setDefaultSectionSize(150);
        tableProcesses->horizontalHeader()->setStretchLastSection(true);
        btnShowAll = new QPushButton(pageProcess);
        btnShowAll->setObjectName("btnShowAll");
        btnShowAll->setGeometry(QRect(20, 30, 171, 31));
        btnSearch = new QPushButton(pageProcess);
        btnSearch->setObjectName("btnSearch");
        btnSearch->setGeometry(QRect(660, 30, 171, 31));
        lineSearch = new QLineEdit(pageProcess);
        lineSearch->setObjectName("lineSearch");
        lineSearch->setGeometry(QRect(390, 30, 251, 31));
        btnKillProcess = new QPushButton(pageProcess);
        btnKillProcess->setObjectName("btnKillProcess");
        btnKillProcess->setGeometry(QRect(210, 30, 111, 31));
        btnKillProcess->setFont(font1);
        stackedWidget->addWidget(pageProcess);
        pageStats = new QWidget();
        pageStats->setObjectName("pageStats");
        ramChartContainer = new QWidget(pageStats);
        ramChartContainer->setObjectName("ramChartContainer");
        ramChartContainer->setGeometry(QRect(20, 30, 431, 411));
        cpuChartContainer = new QWidget(pageStats);
        cpuChartContainer->setObjectName("cpuChartContainer");
        cpuChartContainer->setGeometry(QRect(430, 30, 391, 411));
        stackedWidget->addWidget(pageStats);
        page = new QWidget();
        page->setObjectName("page");
        listWiFiNetworks = new QListWidget(page);
        listWiFiNetworks->setObjectName("listWiFiNetworks");
        listWiFiNetworks->setGeometry(QRect(30, 110, 691, 341));
        labelConnectedWiFi = new QLabel(page);
        labelConnectedWiFi->setObjectName("labelConnectedWiFi");
        labelConnectedWiFi->setGeometry(QRect(260, 40, 331, 51));
        btnRefreshWiFi = new QPushButton(page);
        btnRefreshWiFi->setObjectName("btnRefreshWiFi");
        btnRefreshWiFi->setGeometry(QRect(30, 50, 161, 41));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Ubuntu Sans")});
        font3.setBold(true);
        font3.setItalic(false);
        btnRefreshWiFi->setFont(font3);
        stackedWidget->addWidget(page);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1104, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Linux_Taskmanager", nullptr));
        btnProcessPage->setText(QCoreApplication::translate("MainWindow", "Process_Manager", nullptr));
        btnStatsPage->setText(QCoreApplication::translate("MainWindow", "CPU_RAM_USAGE", nullptr));
        btnWiFiPage->setText(QCoreApplication::translate("MainWindow", "WIFI", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableProcesses->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Pid", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableProcesses->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableProcesses->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "State", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableProcesses->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Memory", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableProcesses->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "User", nullptr));
        btnShowAll->setText(QCoreApplication::translate("MainWindow", "ShowAll", nullptr));
        btnSearch->setText(QCoreApplication::translate("MainWindow", "Search", nullptr));
        btnKillProcess->setText(QCoreApplication::translate("MainWindow", "KILL", nullptr));
        labelConnectedWiFi->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        btnRefreshWiFi->setText(QCoreApplication::translate("MainWindow", "Refresh", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
