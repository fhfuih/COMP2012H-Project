#include <string>
using std::string;

#include "OrbGameWindow.h"
#include "ui_orbgamewindow.h"

OrbGameWindow::OrbGameWindow(Type types[BOARD_ROWS][BOARD_COLS], QWidget *parent) :
    QWidget(parent),
    selected(nullptr),
    ui(new Ui::OrbGameWindow),
    orbAnimationStatus(false)
{
    ui->setupUi(this);
    this->setGeometry(0,0,BOARD_COLS * ORBBOX_WIDTH, BOARD_ROWS * ORBBOX_HEIGHT);
//    this->setStyleSheet("background-image:url(:/resource/blackSquare.png);");
    this->make_grid(types);
}

OrbGameWindow::~OrbGameWindow() {
    delete ui;
    for(int i = 0; i < BOARD_ROWS; ++i) {
        for(int j = 0; j < BOARD_COLS; ++j) {
            delete orbBox[i][j];
        }
    }
}

void OrbGameWindow::closeEvent(QCloseEvent *event) {
    emit closed();
}

void OrbGameWindow::make_grid(Type types[BOARD_ROWS][BOARD_COLS]) {
    for(int i = 0; i < BOARD_ROWS; ++i) {
        for(int j = 0; j < BOARD_COLS; ++j) {
            this->orbBox[i][j] = new OrbBox(i, j, types[i][j], this);
            connect(this->orbBox[i][j], &OrbBox::clicked_with_pos, this, &OrbGameWindow::clicked_orbBox);
            this->orbBox[i][j]->installEventFilter(this);
        }
    }
}

void OrbGameWindow::clicked_orbBox(int row, int col) {
    if (orbAnimationStatus) return;
    if (selected) return;

    selected = orbBox[row][col];
    selected->set_highlighted(true);
    emit orb_selected(row, col);
}

void OrbGameWindow::keyPressEvent(QKeyEvent* event) {
    if (orbAnimationStatus) return;
    if (!selected) return;

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
    if (orbAnimationStatus) return;
    if (!selected) return;

    selected->set_highlighted(false);
    selected = nullptr;
    emit animation_start(true);
    emit orb_deselected();
}

void OrbGameWindow::swap_with(int row, int col) {
    if (orbAnimationStatus) return;
    if (!selected) return;
    if (row < 0 || row >= BOARD_ROWS || col < 0 || col >= BOARD_COLS) return;

    // swap images and types
    OrbBox* dest = orbBox[row][col];
    Type destType = dest->get_type();
    dest->set_type(selected->get_type());
    selected->set_type(destType);
    // move the selection
    selected->set_highlighted(false);
    selected = dest;
    selected->set_highlighted(true);
    emit orb_move_to(row, col);
}

bool OrbGameWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (watched->inherits("QPushButton") && event->type() == QEvent::KeyPress) {
        QKeyEvent* e = static_cast<QKeyEvent*>(event);
        if (e->key() == Qt::Key_Up || e->key() == Qt::Key_Down || e->key() == Qt::Key_Left || e->key() == Qt::Key_Right) {
            this->keyPressEvent(e);
            return true;
        } else {
            return QObject::eventFilter(watched, event);
        }
    }
    return QObject::eventFilter(watched, event);
}

void OrbGameWindow::refresh_board(const vector<BoardState>& statesVector) {
    for(size_t state = 0; state < statesVector.size(); ++state) {
        for(int i = 0; i < BOARD_ROWS; ++i) for(int j = 0; j < BOARD_COLS; ++j) {
            orbBox[i][j]->set_type(statesVector[state].board[i][j]);
        }
        utils_delay(250);
    }
}

void OrbGameWindow::update_orb_animation_status(bool orbAnimationStatus) {
    this->orbAnimationStatus = orbAnimationStatus;
}
