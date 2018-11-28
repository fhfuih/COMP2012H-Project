#include "petbox.h"

PetBox::PetBox(int id, QWidget* parent):
    QPushButton(parent),
    id(id),
    selected(false)
{
    setFlat(true);
    setText("");
    setVisible(true);
    setCursor(Qt::PointingHandCursor);
    setIcon(QIcon(QString(":/resource/%1.png").arg(id)));
    setIconSize(QSize(50,50));
    const int OFF_X = 60;
    const int OFF_Y = 300;
    const int WIDTH = 100;
    const int HEIGHT = 100;
    const int COL = 5;
    int pos = id - 101;
    setGeometry(OFF_X + WIDTH * (pos % COL), OFF_Y + HEIGHT * (pos / COL), WIDTH, HEIGHT);

    connect(this, &QPushButton::clicked, this, &PetBox::on_self_clicked);
}

int PetBox::get_id() {
    return id;
}

bool PetBox::get_selected() {
    return selected;
}

void PetBox::set_selected(bool s) {
    selected = s;
}

void PetBox::enterEvent(QEvent *event) {
    emit mouse_entered(id);
}

void PetBox::on_self_clicked() {
    emit mouse_clicked(id);
}
