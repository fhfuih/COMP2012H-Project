#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QDialog>
#include <QLayout>
#include <QFile>

#include "ButtonWithDagger.h"

namespace Ui {
class AboutWindow;
}

class AboutWindow : public QDialog
{
    Q_OBJECT
    /* The 'About' window. Inherits QDialog so note its different behavior upon closing */
public:
    explicit AboutWindow(QWidget *parent = nullptr);
    virtual ~AboutWindow() override;

private:
    Ui::AboutWindow *ui;

    ButtonWithDagger* ok;
};

#endif // ABOUTWINDOW_H
