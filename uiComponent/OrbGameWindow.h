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

public:
    explicit OrbGameWindow(Type types[BOARD_ROWS][BOARD_COLS], QWidget *parent = nullptr);
    ~OrbGameWindow() override;

private:
    OrbBox* orbBox[BOARD_ROWS][BOARD_COLS];
    OrbBox* selected;

    Ui::OrbGameWindow *ui;

    bool orbAnimationStatus;

    /* helper functions
     * upon board construction and ui response & interaction
     */
    void make_grid(Type types[BOARD_ROWS][BOARD_COLS]);
    /* responding user interactions */
    enum Direction {UP, DOWN, LEFT, RIGHT};
    void deselect();
    void swap_with(int row, int col);

    /* signals and slots */
signals:
    void orb_selected(int row, int col);
    void orb_deselected();
    void orb_move_to(int row, int col);
    void closed();
    void animation_start(bool animationStatus);

public slots:
    void refresh_board(const vector<BoardState>& statesVector);
    void update_orb_animation_status(bool orbAnimationStatus);

private slots:
    void clicked_orbBox(int row, int col);
    void keyPressEvent(QKeyEvent* event) override;
    void closeEvent(QCloseEvent *event) override;
};

#endif // ORBGAMEWINDOW_H
