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

void BigGameWindow::DisplayCombatText (QString text, bool playerAction) {
    if(playerAction) ui->playerList->insertItem(0, text);
    else ui->enemyList->insertItem(0, text);
}
