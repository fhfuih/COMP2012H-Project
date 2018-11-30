#include "biggamewindow.h"
#include "ui_biggamewindow.h"

BigGameWindow::BigGameWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BigGameWindow)
{
    ui->setupUi(this);
}

BigGameWindow::~BigGameWindow()
{
    delete ui;
}
