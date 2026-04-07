#include "mainwindow.h"

#include "ui_mainwindow.h"
#include <QMessageBox>
#include "EVScreen.h"
#include <QTimer>
#include <QRandomGenerator>
#include <QDesktopServices>
#include <QUrl>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    QPixmap pix(":/images/car.png");
    ui->labelCar->setPixmap(pix);

    ui->label->setScaledContents(true);
    ui->label->setPixmap(pix.scaled(ui->label->size(), Qt::KeepAspectRatio));


    alarmShown = false;

    batteryLevel = 100;

    dataTimer = new QTimer(this);
    connect(dataTimer, &QTimer::timeout, this, [=]() {
        QString currentTime = QTime::currentTime().toString("hh:mm:ss AP");
        ui->labelTime->setText(currentTime);

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

            //  show popup only once
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



    if (pix.isNull()) {
        qDebug() << "Image NOT loaded";
    } else {
        qDebug() << "Image loaded OK";
        ui->labelCar->setPixmap(pix);
    }

    connect(ui->btnMap, &QPushButton::clicked, this, [=]() {
        QDesktopServices::openUrl(QUrl("https://www.google.com/maps"));
    });

    connect(ui->btnSearch, &QPushButton::clicked, this, [=]() {
        QString location = ui->lineSearch->text();

        if (!location.isEmpty()) {
            QString url = "https://www.google.com/maps/search/" + location;
            QDesktopServices::openUrl(QUrl(url));
        }
    });

    // connect(ui->btnEV, &QPushButton::clicked, this, [=]() {
    //     ui->stackedWidget->setCurrentIndex(1);
    // });
    connect(ui->btnEV, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentWidget(ui->pageEV);
    });
    connect(ui->btnBack, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentWidget(ui->pageHome);
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
    connect(ui->btnPhone, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentWidget(ui->pagePhone);
    });
    connect(ui->btnBackPhone, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentWidget(ui->pageHome);
    });

    connect(ui->btn1, &QPushButton::clicked, this, [=]() {
        ui->lineNumber->setText(ui->lineNumber->text() + "1");
    });
    connect(ui->btn2, &QPushButton::clicked, this, [=]() {
        ui->lineNumber->setText(ui->lineNumber->text() + "2");
    });
    connect(ui->btn3, &QPushButton::clicked, this, [=]() {
        ui->lineNumber->setText(ui->lineNumber->text() + "3");
    });
    connect(ui->btn4, &QPushButton::clicked, this, [=]() {
        ui->lineNumber->setText(ui->lineNumber->text() + "4");
    });
    connect(ui->btn5, &QPushButton::clicked, this, [=]() {
        ui->lineNumber->setText(ui->lineNumber->text() + "5");
    });
    connect(ui->btn6, &QPushButton::clicked, this, [=]() {
        ui->lineNumber->setText(ui->lineNumber->text() + "6");
    });
    connect(ui->btn7, &QPushButton::clicked, this, [=]() {
        ui->lineNumber->setText(ui->lineNumber->text() + "7");
    });
    connect(ui->btn8, &QPushButton::clicked, this, [=]() {
        ui->lineNumber->setText(ui->lineNumber->text() + "8");
    });
    connect(ui->btn9, &QPushButton::clicked, this, [=]() {
        ui->lineNumber->setText(ui->lineNumber->text() + "9");
    });
    connect(ui->btn0, &QPushButton::clicked, this, [=]() {
        ui->lineNumber->setText(ui->lineNumber->text() + "0");
    });
    connect(ui->btnstar, &QPushButton::clicked, this, [=]() {
        ui->lineNumber->setText(ui->lineNumber->text() + "*");
    });
    connect(ui->btnHash, &QPushButton::clicked, this, [=]() {
        ui->lineNumber->setText(ui->lineNumber->text() + "#");
    });

    connect(ui->btnCall, &QPushButton::clicked, this, [=]() {
        QString number = ui->lineNumber->text();

        if (number.isEmpty()) {
            QMessageBox::warning(this, "Error", "Enter a number");
        } else {
            QMessageBox::information(this, "Calling", "Calling " + number +": ");
        }
    });
    connect(ui->btnEndCall, &QPushButton::clicked, this, [=]() {
        QMessageBox::information(this, "Call Ended", "Call has been terminated");
        ui->lineNumber->clear();   // clear number
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
