#include <string>
using std::string;

#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(Type types[BOARD_ROWS][BOARD_COLS], QWidget *parent) :
    QWidget(parent),
    selected(nullptr),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    this->make_grid(types);
}

GameWindow::GameWindow(QWidget *parent) :
    QWidget(parent),
    selected(nullptr),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    this->make_grid();
}

GameWindow::~GameWindow() {
    delete ui;
    for(int i = 0; i < BOARD_ROWS; ++i) {
        for(int j = 0; j < BOARD_COLS; ++j) {
            delete square[i][j];
        }
    }
}

void GameWindow::closeEvent(QCloseEvent *event) {
    emit closed();
}

void GameWindow::make_grid() {
    for(int i = 0; i < BOARD_ROWS; ++i) {
        for(int j = 0; j < BOARD_COLS; ++j) {
            Type _type = static_cast<Type>(rand()%TYPE_COUNT + 1);
            this->square[i][j] = new Square(i, j, _type, this);
            connect(this->square[i][j], &Square::clicked_with_pos, this, &GameWindow::clicked_square);
        }
    }
}

void GameWindow::make_grid(Type types[BOARD_ROWS][BOARD_COLS]) {
    for(int i = 0; i < BOARD_ROWS; ++i) {
        for(int j = 0; j < BOARD_COLS; ++j) {
            this->square[i][j] = new Square(i, j, types[i][j], this);
            connect(this->square[i][j], &Square::clicked_with_pos, this, &GameWindow::clicked_square);
        }
    }
}

void GameWindow::make_hp() {

}

void GameWindow::clicked_square(int row, int col) {
    if (selected) {
        return;
    }
    selected = square[row][col];
    selected->set_highlighted(true);
    emit orb_selected(row, col);
}

void GameWindow::keyPressEvent(QKeyEvent* event) {
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

void GameWindow::deselect() {
    if (!selected) {
        return;
    }
    selected->set_highlighted(false);
    selected = nullptr;
    emit orb_deselected();
}

void GameWindow::swap_with(int row, int col) {
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
