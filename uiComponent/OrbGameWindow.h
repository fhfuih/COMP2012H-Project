#ifndef ORBGAMEWINDOW_H
#define ORBGAMEWINDOW_H

#include <QWidget>
#include <QCloseEvent>
#include <QKeyEvent>
//#include <QDebug>

#include "Utils.h"
#include "square.h"

namespace Ui {
class OrbGameWindow;
}

class Square;

class OrbGameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit OrbGameWindow(Type types[BOARD_ROWS][BOARD_COLS], QWidget *parent = nullptr);
    explicit OrbGameWindow(QWidget *parent = nullptr); // this overload should be used in test env only
    ~OrbGameWindow() override;

private:
    Square* square[BOARD_ROWS][BOARD_COLS];
    Square* selected;

    Ui::OrbGameWindow *ui;

    /* helper functions
     * upon board construction and ui response & interaction
     */
    void make_grid(); // this overload should be used in test env only
    void make_grid(Type types[BOARD_ROWS][BOARD_COLS]);
    void make_hp();
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

private slots:
    void clicked_square(int row, int col);
    void keyPressEvent(QKeyEvent* event) override;
    void closeEvent(QCloseEvent *event) override;
};

#endif // ORBGAMEWINDOW_H
