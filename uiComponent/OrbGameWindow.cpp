#include <string>
using std::string;

#include "OrbGameWindow.h"
#include "ui_orbgamewindow.h"

OrbGameWindow::OrbGameWindow(Type types[BOARD_ROWS][BOARD_COLS], QWidget *parent) :
    QWidget(parent),
    selected(nullptr),
    ui(new Ui::OrbGameWindow)
{
    ui->setupUi(this);
    this->setGeometry(0,0,BOARD_COLS * SQUARE_WIDTH, BOARD_ROWS * SQUARE_HEIGHT);
    this->make_grid(types);
}

OrbGameWindow::OrbGameWindow(QWidget *parent) :
    QWidget(parent),
    selected(nullptr),
    ui(new Ui::OrbGameWindow)
{
    ui->setupUi(this);
    this->make_grid();
}

OrbGameWindow::~OrbGameWindow() {
    delete ui;
    for(int i = 0; i < BOARD_ROWS; ++i) {
        for(int j = 0; j < BOARD_COLS; ++j) {
            delete square[i][j];
        }
    }
}

void OrbGameWindow::closeEvent(QCloseEvent *event) {
    emit closed();
}

void OrbGameWindow::make_grid() {
    for(int i = 0; i < BOARD_ROWS; ++i) {
        for(int j = 0; j < BOARD_COLS; ++j) {
            Type _type = static_cast<Type>(rand()%TYPE_COUNT + 1);
            this->square[i][j] = new Square(i, j, _type, this);
            connect(this->square[i][j], &Square::clicked_with_pos, this, &OrbGameWindow::clicked_square);
        }
    }
}

void OrbGameWindow::make_grid(Type types[BOARD_ROWS][BOARD_COLS]) {
    for(int i = 0; i < BOARD_ROWS; ++i) {
        for(int j = 0; j < BOARD_COLS; ++j) {
            this->square[i][j] = new Square(i, j, types[i][j], this);
            connect(this->square[i][j], &Square::clicked_with_pos, this, &OrbGameWindow::clicked_square);
        }
    }
}

void OrbGameWindow::make_hp() {

}

void OrbGameWindow::clicked_square(int row, int col) {
    if (selected) {
        return;
    }
    selected = square[row][col];
    selected->set_highlighted(true);
    emit orb_selected(row, col);
}

void OrbGameWindow::keyPressEvent(QKeyEvent* event) {
    if (!selected) {
        return;
    }
    switch (event->key()) {
    case Qt::Key_Return:
        deselect();
        break;
    case 'W':
    case Qt::Key_Up:
        swap_with(selected->get_row() + 1, selected->get_col());
        break;
    case 'S':
    case Qt::Key_Down:
        swap_with(selected->get_row() - 1, selected->get_col());
        break;
    case 'A':
    case Qt::Key_Left:
        swap_with(selected->get_row(), selected->get_col() - 1);
        break;
    case 'D':
    case Qt::Key_Right:
        swap_with(selected->get_row(), selected->get_col() + 1);
        break;
    }

}

void OrbGameWindow::deselect() {
    if (!selected) {
        return;
    }
    selected->set_highlighted(false);
    selected = nullptr;
    emit orb_deselected();
}

void OrbGameWindow::swap_with(int row, int col) {
    if (!selected) {
        return;
    }
    if (row < 0 || row >= BOARD_ROWS || col < 0 || col >= BOARD_COLS) {
        return;
    }
    // swap images and types
    Square* dest = square[row][col];
    Type destType = dest->get_type();
    dest->set_type(selected->get_type());
    selected->set_type(destType);
    // move the selection
    selected->set_highlighted(false);
    selected = dest;
    selected->set_highlighted(true);
    emit orb_move_to(row, col);
}
