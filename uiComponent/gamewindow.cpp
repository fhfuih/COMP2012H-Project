#include <string>
using std::string;

#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "square.h"
#include "OrbGame.h"

GameWindow::GameWindow(QWidget *parent, OrbGame* orb_game) :
    QWidget(parent),
    ui(new Ui::GameWindow),
    orb_game(orb_game)
{
    ui->setupUi(this);
    this->make_grid();
}

GameWindow::~GameWindow() {
    delete ui;
    for(int i = 0; i < 5; ++i) for(int j = 0; i < 6; ++j) delete square[i][j];
}

OrbGame* GameWindow::get_orb_game() {
    return orb_game;
}

Square* GameWindow::get_square(int row, int col) const {
    return this->square[row][col];
}

void GameWindow::set_highlighted(int row, int col, bool value) {
    this->square[row][col]->set_highlighted(value, "black")
}
    
void GameWindow::closeEvent(QCloseEvent *event) override {
    emit closed();
}

void GameWindow::make_grid() {
    for(int i = 0; i < 5; ++i) for(int j = 0; i < 6; ++j) this->square[i][j] = new Square(this, i, j);
}

#endif // GAMEWINDOW_H
