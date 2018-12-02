#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QWidget>

#include "ButtonWithDagger.h"
#include "SelectionWindow.h"
#include "AboutWindow.h"

namespace Ui {
class StartWindow;
}

class StartWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StartWindow(QWidget *parent = nullptr);
    ~StartWindow();

private:
    Ui::StartWindow *ui;

    ButtonWithDagger* start;
    ButtonWithDagger* quit;
    ButtonWithDagger* about;

    AboutWindow aboutWindow;
    MainWindow* mainWindow;

private slots:
    void on_startClicked();
    void on_mainWindowClosed();
};

#endif // STARTWINDOW_H
