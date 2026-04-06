#ifndef EVSCREEN_H
#define EVSCREEN_H

#include <QDialog>

namespace Ui {
class EVScreen;
}

class EVScreen : public QDialog
{
    Q_OBJECT

public:
    explicit EVScreen(QWidget *parent = nullptr);
    ~EVScreen();

private:
    Ui::EVScreen *ui;
};

#endif // EVSCREEN_H
