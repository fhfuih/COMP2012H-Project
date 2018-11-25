#ifndef OrbGame_h
#define OrbGame_h

#include <QObject>
#include <QKeyEvent>
using std::vector;

#include "gamewindow.h"
#include "square.h"

class GameWindow; //game window ui

class OrbGame : QObject {
    Q_OBJECT
public:
    OrbGame();
    ~OrbGame();
    GameWindow* get_game_window() const;

private:
    GameWindow* game_window; //game window ui
    Type orbBoard[BOARD_ROWS][BOARD_COLS]; //Orb game board
    
    vector<int[2]> combos; //{type, orb count}
    vector<Type[BOARD_ROWS][BOARD_COLS]> boardStates;
    
    void process_combos();
    void shift_orbs();
    void refill_board();
    
private slots:
    void on_return_key(Type orbBoard[BOARD_ROWS][BOARD_COLS]);
    
signals:
    void combo_finish(vector<int[2]> combos);
    void refresh_board(vector<Type[BOARD_ROWS][BOARD_COLS]> boardStates);
};

#endif /* OrbGame_h */
