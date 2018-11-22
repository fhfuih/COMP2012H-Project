#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QCloseEvent>

namespace Ui {
class GameWindow;
}

class Square;
class OrbGame;

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr, OrbGame* orb_game = nullptr);
    ~GameWindow() override;

    OrbGame* get_orb_game();
    Square* get_square(int row, int col) const;
    void set_highlighted(int row, int col, bool value);
    void reset_highlighted();

private:
    void closeEvent(QCloseEvent *event) override;
    void make_grid();

    Ui::GameWindow *ui;
    Square* square[5][6];
    OrbGame* orb_game;

signals:
    void closed();
};

#endif // GAMEWINDOW_H
