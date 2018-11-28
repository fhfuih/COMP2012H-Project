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
}

StartWindow::~StartWindow()
{
    delete start;
    delete quit;
    delete about;
    delete ui;
}

void StartWindow::on_start_clicked()
{
    mainWindow = new MainWindow;
    mainWindow->show();
    this->hide();
}

void StartWindow::on_about_clicked()
{
    aboutWindow.exec();
}

void StartWindow::on_quit_clicked()
{
    this->close();
}

void StartWindow::on_mainWindow_closed()
{
    delete mainWindow;
}

