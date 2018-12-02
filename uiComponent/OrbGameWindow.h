#ifndef ORBGAMEWINDOW_H
#define ORBGAMEWINDOW_H

#include <QWidget>
#include <QCloseEvent>
#include <QKeyEvent>
#include <QTime>
#include <QCoreApplication>
using std::vector;

#include "Utils.h"
#include "OrbBox.h"

namespace Ui {
class OrbGameWindow;
}

class OrbBox;

class OrbGameWindow : public QWidget
{
    Q_OBJECT
    /* Wrapper of orb chessboard
     * block invalid user interactions
     * and only signals the backend when user performs a valid operation
     * and after the frontend UI has revealed this operation
     * derived from PA4 but has heavily modified to simplify the
     * interface and the overall logic */
public:
    explicit OrbGameWindow(Type types[BOARD_ROWS][BOARD_COLS], QWidget *parent = nullptr);
    ~OrbGameWindow() override;

private:
    OrbBox* orbBox[BOARD_ROWS][BOARD_COLS];
    OrbBox* selected;

    Ui::OrbGameWindow *ui;

    bool orbAnimationStatus;
    bool gameOver;

    /* board construction and ui response & interaction */
    void make_grid(Type types[BOARD_ROWS][BOARD_COLS]);
    /* responding user interactions */
    void deselect();
    void swap_with(int row, int col);

    /* Prevent orb listening arrow keys */
    bool eventFilter(QObject *watched, QEvent *event) override;

    /* signals as interface to connect with backend */
signals:
    void orb_selected(int row, int col);
    void orb_deselected();
    void orb_move_to(int row, int col);
    void closed();
    void animation_start(bool animationStatus);

    /* Public slots for GameInstace to connet with backend */
public slots:
    void refresh_board(const vector<BoardState>& statesVector);
    void update_orb_animation_status(bool orbAnimationStatus);
    void game_over();

private slots:
    void clicked_orbBox(int row, int col);
    void keyPressEvent(QKeyEvent* event) override;
    void closeEvent(QCloseEvent *event) override;
};

#endif // ORBGAMEWINDOW_H
