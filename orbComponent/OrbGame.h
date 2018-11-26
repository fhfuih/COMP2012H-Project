#ifndef OrbGame_h
#define OrbGame_h

#include <QObject>
#include <QKeyEvent>
using std::vector;

#include "Orb.h"
#include "gamewindow.h"
#include "OrbGameWindow.h"

class GameWindow; //game window ui

class OrbGame : public QObject {
    Q_OBJECT
public:
    OrbGame();
    ~OrbGame();

private:
    GameWindow* game_window;

    Type orbBoard[BOARD_ROWS][BOARD_COLS];
    int selectedOrbRow;
    int selectedOrbCol;
    Type selectedType;
    
    vector<Combo> combosVector;
    vector<BoardState> statesVector;
    
    void process_combos();
    void shift_orbs();
    void refill_board();

    void generate_board(Type orbBoard[BOARD_ROWS][BOARD_COLS]);
    
public slots:
    void on_mouse_click(int row, int col);
    void on_arrow_key(int row, int col);
    void on_return_key();
    
signals:
    void combo_finish(const vector<Combo>& combos);
    void refresh_board(const vector<BoardState>& statesVector);
};

#endif /* OrbGame_h */
