#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "EVScreen.h"
#include <QTimer>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    alarmShown = false;

    batteryLevel = 100;

    dataTimer = new QTimer(this);
    connect(dataTimer, &QTimer::timeout, this, [=]() {

        // simulate battery drain
        batteryLevel -= QRandomGenerator::global()->bounded(0, 3);

        if (batteryLevel < 0)
            batteryLevel = 100;

        // update UI
        ui->labelBattery->setText(QString::number(batteryLevel) + "%");
        ui->batteryBar->setValue(batteryLevel);

        // MOVE WARNING LOGIC HERE
        if (batteryLevel < 15) {

            ui->labelStatus->setText("CRITICAL");
            ui->labelStatus->setStyleSheet("color: red; font-weight: bold;");
            ui->batteryBar->setStyleSheet("QProgressBar::chunk { background-color: red; }");

            // ✅ show popup only once
            if (!alarmShown) {
                QMessageBox::warning(this, "ALERT", "Battery Critical!");
                qDebug() << "ALARM: Battery critical at" << batteryLevel << "%";
                alarmShown = true;
            }
        }
        else if (batteryLevel < 30) {

            ui->labelStatus->setText("LOW");
            ui->labelStatus->setStyleSheet("color: yellow; font-weight: bold;");
            ui->batteryBar->setStyleSheet("QProgressBar::chunk { background-color: yellow; }");

            alarmShown = false;   // reset when not critical
        }
        else {

            ui->labelStatus->setText("OK");
            ui->labelStatus->setStyleSheet("color: green;");
            ui->batteryBar->setStyleSheet("QProgressBar::chunk { background-color: #22c55e; }");

            alarmShown = false;   // reset when normal
        }

    });
    dataTimer->start(1000);  // every 1 second


    QPixmap pix(":/images/car.png");

    if (pix.isNull()) {
        qDebug() << "Image NOT loaded";
    } else {
        qDebug() << "Image loaded OK";
        ui->labelCar->setPixmap(pix);
    }


    connect(ui->btnEV, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(1);
    });
    connect(ui->btnBack, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(0);
    });

    connect(ui->btnMap, &QPushButton::clicked, this, [=]() {
        qDebug() << "Map button clicked";
    });

    connect(ui->btnNav, &QPushButton::clicked, this, [=]() {
        qDebug() << "Navigation button clicked";
    });

    connect(ui->btnPhone, &QPushButton::clicked, this, [=]() {
        qDebug() << "Phone button clicked";
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
