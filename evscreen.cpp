#include "evscreen.h"
#include "ui_evscreen.h"

EVScreen::EVScreen(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EVScreen)
{
    ui->setupUi(this);
}

EVScreen::~EVScreen()
{
    delete ui;
}
