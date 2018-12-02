#include "ButtonWithDagger.h"
#include "ui_ButtonWithDagger.h"

ButtonWithDagger::ButtonWithDagger(const QString& text, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ButtonWithDagger)
{
    ui->setupUi(this);
    auto sp = ui->dagger->sizePolicy();
    sp.setRetainSizeWhenHidden(true);
    ui->dagger->setSizePolicy(sp);
    ui->dagger->hide();
    ui->pushButton->setText(text);
    ui->pushButton->setCursor(Qt::PointingHandCursor);

    ui->pushButton->installEventFilter(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &ButtonWithDagger::on_pressingButton);
}

ButtonWithDagger::~ButtonWithDagger()
{
    delete ui;
}

void ButtonWithDagger::setText(const QString &text) {
    ui->pushButton->setText(text);
}

bool ButtonWithDagger::eventFilter(QObject *watched, QEvent *event) {
    if (watched == ui->pushButton) {
        if (event->type() == QEvent::HoverEnter) {
            ui->dagger->show();
            return true;
        } else if (event->type() == QEvent::HoverLeave) {
            ui->dagger->hide();
            return true;
        }
    }
    return false;
}

void ButtonWithDagger::on_pressingButton() {
    emit clicked();
}
