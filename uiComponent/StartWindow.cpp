#include "StartWindow.h"
#include "ui_StartWindow.h"

StartWindow::StartWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartWindow),
    start(new ButtonWithDagger{"Start Game"}),
    quit(new ButtonWithDagger{"Quit Game"}),
    about(new ButtonWithDagger{"About"})
{
    ui->setupUi(this);

    ui->MenuLayout->addWidget(start);
    ui->MenuLayout->addWidget(quit);
    ui->MenuLayout->addWidget(about);
    connect(start, &ButtonWithDagger::clicked, this, &StartWindow::on_startClicked);
    connect(about, &ButtonWithDagger::clicked, &aboutWindow, &AboutWindow::exec);
    connect(quit, &ButtonWithDagger::clicked, this, &StartWindow::close);
}

StartWindow::~StartWindow()
{
    delete start;
    delete quit;
    delete about;
    delete ui;
}

void StartWindow::on_startClicked()
{
    mainWindow = new MainWindow;
    connect(mainWindow, &MainWindow::closed, this, &StartWindow::on_mainWindowClosed);
    mainWindow->show();
    this->hide();
}

void StartWindow::on_mainWindowClosed()
{
    qDebug() << "main window closed";
    mainWindow->deleteLater();
    this->show();
}

