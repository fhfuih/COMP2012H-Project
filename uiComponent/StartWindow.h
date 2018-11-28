#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QWidget>

#include "buttonwithdagger.h"
#include "mainwindow.h"
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
    void on_start_clicked();
    void on_about_clicked();
    void on_quit_clicked();
    void on_mainWindow_closed();
};

#endif // STARTWINDOW_H
