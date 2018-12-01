#include "biggamewindow.h"
#include "ui_biggamewindow.h"

BigGameWindow::BigGameWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BigGameWindow)
{
    ui->setupUi(this);
    this->installEventFilter(this);
}

BigGameWindow::~BigGameWindow()
{
    delete ui;
}

bool BigGameWindow::eventFilter(QObject *watched, QEvent *event)
{
    // qDebug() << event->type() << " event on " << watched->objectName();
    return false;
}

void BigGameWindow::DisplayCombatText (QString text, bool playerAction) {
    if(playerAction) ui->playerList->insertItem(0, text);
    else ui->enemyList->insertItem(0, text);
}
