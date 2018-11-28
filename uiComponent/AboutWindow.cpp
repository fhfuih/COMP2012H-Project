#include "AboutWindow.h"
#include "ui_AboutWindow.h"

AboutWindow::AboutWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutWindow),
    ok(new ButtonWithDagger{"OK"})
{
    ui->setupUi(this);
    ui->ButtonLayout->addWidget(ok);
    connect(ok, &ButtonWithDagger::clicked, this, &AboutWindow::close);

    QFile about{":/about.txt"};
    if (about.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ui->AboutText->setText(about.readAll());
    } else {
        ui->AboutText->setText("About file not found");
    }
}

AboutWindow::~AboutWindow()
{
    delete ok;
    delete ui;
}
