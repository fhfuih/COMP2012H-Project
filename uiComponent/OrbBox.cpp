#include <sstream>
#include <QDebug>
#include <QString>

#include "OrbBox.h"

using std::string;
using std::ostringstream;

OrbBox::OrbBox(int _row, int _col, Type _type, QWidget* parent) :
    QPushButton(parent),
    row(_row),
    col(_col),
    is_highlighted(false),
    type(_type)
{
    this->render();
    this->render_image();
    connect(this, &OrbBox::clicked, this, &OrbBox::clicked_handler);
}

void OrbBox::render() {
    setGeometry(QRect(OFFSET_X + ORBBOX_WIDTH * this->col, OFFSET_Y + ORBBOX_HEIGHT * (BOARD_ROWS - this->row - 1), ORBBOX_WIDTH, ORBBOX_HEIGHT));
    setVisible(true);
    setFlat(true);
    setAutoFillBackground(true);
    setText("");
    setStyle("border-color", "white");
    setStyle("border-width", "5px");
    setStyle("border-style", "solid");
//    setStyle("background-color", "black");
    applyStyle();
}

void OrbBox::render_image() {
    ostringstream os;
    os << "url(:/resource/Orb" << static_cast<int>(type) << ".png)";
    setStyle("background-image", os.str());
    applyStyle();
}

void OrbBox::setStyle(string key, string value) {
    this->style[key] = value;
}

void OrbBox::applyStyle() {
    ostringstream s;
    for (StyleMap::iterator i=this->style.begin(); i!=this->style.end(); i++) {
        s << i->first << ":" << i->second << ";";
    }
    string style_string = s.str();
    setStyleSheet(QString::fromStdString(style_string));
}

void OrbBox::set_highlighted(bool value, string color) {
    if (value) {
        setStyle("border-color", color);
    }
    else {
        setStyle("border-color", "white");
    }
    applyStyle();
    this->is_highlighted=value;
}

bool OrbBox::get_highlighted() const {
    return this->is_highlighted;
}

void OrbBox::clicked_handler() {
    emit clicked_with_pos(this->row, this->col);
}

Type OrbBox::get_type() const {
    return type;
}

void OrbBox::set_type(Type type) {
    this->type = type;
    render_image();
}

int OrbBox::get_row() const {
    return row;
}

int OrbBox::get_col() const {
    return col;
}
