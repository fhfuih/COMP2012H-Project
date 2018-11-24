#include <sstream>
#include <QDebug>
#include <QString>

#include "square.h"

using std::string;
using std::ostringstream;

Square::Square(int _row, int _col, Type _type, QWidget* parent) :
    QPushButton(parent),
    row(_row),
    col(_col),
    is_highlighted(false),
    type(_type)
{
    this->render();
    this->render_image();
    connect(this, &Square::clicked, this, &Square::clicked_handler);
}

void Square::render() {
    setGeometry(QRect(OFFSET_X + SQUARE_WIDTH * this->col, OFFSET_Y + SQUARE_HEIGHT * (BOARD_ROWS - this->row - 1), SQUARE_WIDTH, SQUARE_HEIGHT));
    setVisible(true);
    setFlat(true);
    setAutoFillBackground(true);
    setText("");
    setStyle("border-color", "white");
    setStyle("border-width", "5px");
    setStyle("border-style", "inset");
//    setStyle("background-color", "black");
    applyStyle();
}

void Square::render_image() {
    ostringstream os;
    os << "url(:/image/resource/orb_" << static_cast<int>(type) << ".png)";
    setStyle("background-image", os.str());
    applyStyle();
}

void Square::setStyle(string key, string value) {
    this->style[key] = value;
}

void Square::applyStyle() {
    ostringstream s;
    for (StyleMap::iterator i=this->style.begin(); i!=this->style.end(); i++) {
        s << i->first << ":" << i->second << ";";
    }
    string style_string = s.str();
    setStyleSheet(QString::fromStdString(style_string));
}

void Square::set_highlighted(bool value, string color) {
    if (value) {
        setStyle("border-color", color);
        setStyle("border-width", "5px");
        setStyle("border-style", "inset");
    }
    else {
        setStyle("border-color", "white");
        setStyle("border-width", "5px");
        setStyle("border-style", "inset");
    }
    applyStyle();
    this->is_highlighted=value;
}

bool Square::get_highlighted() const {
    return this->is_highlighted;
}

void Square::clicked_handler() {
    emit clicked_with_pos(this->row, this->col);
}

Type Square::get_type() const {
    return type;
}

void Square::set_type(Type type) {
    this->type = type;
    render_image();
}

int Square::get_row() const {
    return row;
}

int Square::get_col() const {
    return col;
}
