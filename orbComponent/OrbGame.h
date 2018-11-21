#ifndef OrbGame_h
#define OrbGame_h

#include "Orb.h"

#include <vector>
#include <QObject>
#include <QKeyEvent>

#include "gamewindow.h" //game window ui

using std::vector;

class GameWindow; //game window ui

class OrbGame : QObject {
    Q_OBJECT
public:
    OrbGame();
    ~OrbGame();
    void startGraphicUI();
    GameWindow* get_game_window() const;

private:
    GameWindow* game_window; //game window ui
    Orb* orbBoard[5][6]; //Orb game board
    
    Orb* selectedOrb;
    bool spinning;
    vector<vector<int>> combos; //{type, orb count}
    
    void refresh_board();
    void select_orb(int row, int col);
    void move_orb(int moveRow, int moveCol);
    void process_combos();
    void shift_orbs();
    void refill_board();
    
private slots:
    void on_orb_click(int row, int col);
    void on_arrow_key(int KEY);
    void on_return_key();
    
signals:
    void spin_finish(vector<vector<int>> combos);
};

#endif /* OrbGame_h */
