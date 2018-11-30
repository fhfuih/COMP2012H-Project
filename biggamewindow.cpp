#include "biggamewindow.h"
#include "ui_biggamewindow.h"

BigGameWindow::BigGameWindow(QWidget *parent):
    QWidget(parent),
    ui(new Ui::BigGameWindow)
{
    ui->setupUi(this);
    this->setGeometry(0,0,COMBAT_WINDOW_WIDTH, COMBAT_WINDOW_HEIGHT + ORB_WINDOW_HEIGHT);
}

BigGameWindow::~BigGameWindow(){
    delete ui;
}
