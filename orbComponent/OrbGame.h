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
    Type* selectedOrb;
    
    vector<Combo> combosVector;
    vector<BoardState> statesVector;
    
    void process_combos();
    void shift_orbs();
    void refill_board();

    void generate_board();
    
private slots:
    void on_mouse_click(int row, int col);
    void on_return_key();
    void on_arrow_key(int row, int col);
    
signals:
    void combo_finish(const vector<Combo>& combos);
    void refresh_board(const vector<BoardState>& statesVector);
};

#endif /* OrbGame_h */
