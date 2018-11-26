#ifndef OrbGame_h
#define OrbGame_h

#include <QObject>
#include <QKeyEvent>
using std::vector;

#include "gamewindow.h"

class GameWindow; //game window ui

class OrbGame : public QObject {
    Q_OBJECT
public:
    OrbGame();
    ~OrbGame();
    GameWindow* get_game_window() const;

private:
    GameWindow* game_window; //game window ui
    Type orbBoard[BOARD_ROWS][BOARD_COLS]; //Orb game board
    
    vector<Combo> combosVector;
    vector<BoardState> statesVector;
    
    void process_combos();
    void shift_orbs();
    void refill_board();
    
private slots:
    void on_return_key(Type orbBoard[BOARD_ROWS][BOARD_COLS]);
    
signals:
    void combo_finish(vector<Combo> combos);
    void refresh_board(vector<BoardState> statesVector);
};

#endif /* OrbGame_h */
