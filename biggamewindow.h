#ifndef BIGGAMEWINDOW_H
#define BIGGAMEWINDOW_H

#include <QWidget>

namespace Ui {
class BigGameWindow;
}

class BigGameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit BigGameWindow(QWidget *parent = nullptr);
    ~BigGameWindow();

private:
    Ui::BigGameWindow *ui;
};

#endif // BIGGAMEWINDOW_H
