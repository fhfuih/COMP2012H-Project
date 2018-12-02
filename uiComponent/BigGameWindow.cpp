#include "BigGameWindow.h"
#include "ui_BigGameWindow.h"

BigGameWindow::BigGameWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BigGameWindow)
{
    ui->setupUi(this);
//    this->installEventFilter(this);
}

BigGameWindow::~BigGameWindow()
{
    delete ui;
}

//bool BigGameWindow::eventFilter(QObject *watched, QEvent *event)
//{
//    return false;
//}

void BigGameWindow::DisplayCombatText (QString text, bool playerAction) {
    if(playerAction) ui->playerList->insertItem(0, text);
    else ui->enemyList->insertItem(0, text);
}
