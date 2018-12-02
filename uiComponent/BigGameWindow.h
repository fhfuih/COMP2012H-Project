#ifndef BIGGAMEWINDOW_H
#define BIGGAMEWINDOW_H

#include <QWidget>
#include <Utils.h>

namespace Ui {
class BigGameWindow;
}

class BigGameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit BigGameWindow(QWidget *parent = nullptr);
    ~BigGameWindow();

//    virtual bool eventFilter(QObject* watched, QEvent* event) override;

private:
    Ui::BigGameWindow *ui;

public slots:
    void DisplayCombatText (QString text, bool playerAction);
};

#endif // BIGGAMEWINDOW_H
