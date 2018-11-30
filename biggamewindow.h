#ifndef BIGGAMEWINDOW_H
#define BIGGAMEWINDOW_H

#include <QWidget>
#include "Utils.h"
#include "OrbBox.h"

namespace Ui {
class BigGameWindow;
}


class BigGameWindow : public QWidget
{
    Q_OBJECT

public:
    BigGameWindow(QWidget *parent = nullptr);
    ~BigGameWindow();

private:
    Ui::BigGameWindow *ui;

};

#endif // BIGGAMEWINDOW_H
